/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:48:25 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 10:39:20 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_validoption(char c)
{
	if (c == 'l' || c == 'r' || c == 'R' || c == 'G'
			|| c == 't' || c == 'a')
		return (1);
	return (0);
}

char	**check_option(int *argc, char **argv, int *opts)
{
	int		i;

	i = 1;
	*opts = 0;
	if (*argc < 2 || argv[1][0] != '-')
		return (argv);
	while (argv[1][i])
	{
		if (!is_validoption(argv[1][i]))
			illegal_option(argv[1][i]);
		i++;
	}
	*opts |= ft_strchr(argv[1], 'l') ? LL : 0;
	*opts |= ft_strchr(argv[1], 'r') ? LR : 0;
	*opts |= ft_strchr(argv[1], 'R') ? CR : 0;
	*opts |= ft_strchr(argv[1], 't') && !MATCH(*opts, LR) ? LT : 0;
	*opts |= ft_strchr(argv[1], 'a') ? LA : 0;
	*opts |= ft_strchr(argv[1], 'G') ? CG : 0;
	if (*opts & (LL | LR | CR | LT | LA | CG))
	{
		argv += 1;
		*argc -= 1;
	}
	return (argv);
}
