/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:48:25 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 16:06:28 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_validoption(char c)
{
	if (c == 'l' || c == 'r' || c == 'R'
			|| c == 't' || c == 'a')
		return (1);
	return (0);
}

char	**check_option(int *argc, char **argv, t_options *opts)
{
	int		i;

	i = 1;
	if (*argc < 2 || argv[1][0] != '-')
		return (argv);
	while (argv[1][i])
	{
		if (!is_validoption(argv[1][i]))
			illegal_option(argv[1][i]);
		i++;
	}
	opts->l = ft_strchr(argv[1], 'l') ? 1 : 0;
	opts->r = ft_strchr(argv[1], 'r') ?  1 : 0;
	opts->c_r = ft_strchr(argv[1], 'R') ?  1 : 0;
	opts->t = ft_strchr(argv[1], 't') ?  1 : 0;
	opts->a = ft_strchr(argv[1], 'a') ?  1 : 0;
	if (opts->l || opts->r || opts->c_r || opts->t || opts->a)
	{
		argv += 1;
		*argc -= 1;
	}
	return (argv);
}
