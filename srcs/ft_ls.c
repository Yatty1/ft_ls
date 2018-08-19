/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:26 by syamada           #+#    #+#             */
/*   Updated: 2018/08/18 21:25:16 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		process_input(char **v, int opts, int argc)
{
	int		j;
	DIR		*dir;

	j = 0;
	while (v[j])
	{
		if (!(dir = opendir(v[j])))
			get_file(v[j++], opts);
		else
		{
			if (argc > 2)
				j == 0 ? ft_printf("%s:\n", v[j]) : ft_printf("\n%s:\n", v[j]);
			openread_dir(v[j++], opts);
		}
	}
}

int				main(int argc, char **argv)
{
	char			**input;
	int				opts;
	int				i;
	int				j;

	i = 1;
	j = 0;
	argv = check_option(&argc, argv, &opts);
	if (argc == 1)
		openread_dir(ft_strdup("."), opts);
	input = (char **)malloc(sizeof(char *) * argc);
	while (argv[i])
		input[j++] = ft_strdup(argv[i++]);
	input[j] = 0;
	quick_sort(&input, 0, argc - 2, !MATCH(opts, LR));
	process_input(input, opts, argc);
	delete_input(input);
	while (1);
	return (0);
}
