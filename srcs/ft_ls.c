/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:26 by syamada           #+#    #+#             */
/*   Updated: 2018/08/19 17:03:45 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		one_case(int opts)
{
	char	*str;

	str = ft_strdup(".");
	openread_dir(str, opts);
	ft_strdel(&str);
	exit(0);
}

char			**convert_input(char **argv, int argc)
{
	char	**in;
	int		j;

	j = 0;
	in = (char **)malloc(sizeof(char *) * argc);
	while (*++argv)
		in[j++] = ft_strdup(*argv);
	in[j] = 0;
	return (in);
}

int				main(int argc, char **argv)
{
	DIR				*dir;
	char			**in;
	int				opts;
	int				j;

	argv = check_option(&argc, argv, &opts);
	if (argc == 1)
		one_case(opts);
	in = convert_input(argv, argc);
	quick_sort(in, 0, argc - 2, !MATCH(opts, LR));
	j = 0;
	while (in[j])
	{
		if (!(dir = opendir(in[j])))
			get_file(in[j++], opts);
		else
		{
			if (argc > 2)
				j == 0 ? ft_printf("%s:\n", in[j])
					: ft_printf("\n%s:\n", in[j]);
			openread_dir(in[j++], opts);
		}
	}
	return (0);
}
