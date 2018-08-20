/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 07:48:59 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 15:39:26 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int		partition(char **input, int left, int right, int is_asc)
{
	int		pivot;
	int		j;
	int		i;

	i = left;
	j = left;
	pivot = right;
	while (j < pivot)
	{
		if (is_asc ? ft_strcmp(input[j], input[pivot]) <= 0
				: ft_strcmp(input[j], input[pivot]) >= 0)
			swap_str(&input[i++], &input[j]);
		j++;
	}
	swap_str(&input[i], &input[right]);
	return (i);
}

void			quick_sort(char **input, int left, int right, int is_asc)
{
	int		pivot;

	if (left >= right)
		return ;
	pivot = partition(input, left, right, is_asc);
	quick_sort(input, left, pivot - 1, is_asc);
	quick_sort(input, pivot + 1, right, is_asc);
}

t_meta			*dispatch_sort(t_meta **data, int opts)
{
	if (MATCH(opts, LT))
		return (time_sort(data));
	return (bubble_sort(data, !MATCH(opts, LR)));
}
