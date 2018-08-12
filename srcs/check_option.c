/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:48:25 by syamada           #+#    #+#             */
/*   Updated: 2018/08/12 14:48:47 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**check_option(int *argc, char **argv, t_options *opts)
{
	int		i;

	i = 1;
	opts->l = 0;
	opts->r = 0;
	opts->c_r = 0;
	opts->t = 0;
	opts->a = 0;
	if (*argc < 2 || argv[1][0] != '-')
		return (argv);
	while (argv[1][i])
	{
		opts->l = argv[1][i] == 'l' ? 1 : opts->l;
		opts->r = argv[1][i] == 'r' ?  1 : opts->r;
		opts->c_r = argv[1][i] == 'R' ? 1 : opts->c_r;
		opts->t = argv[1][i] == 't' ? 1 : opts->t;
		opts->a = argv[1][i] == 'a' ? 1 : opts->a;
		i++;
	}
	if (opts->l || opts->r || opts->c_r || opts->t || opts->a)
	{
		argv += 1;
		*argc -= 1;
	}
	return (argv);
}

