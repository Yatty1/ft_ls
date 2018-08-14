/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 07:48:59 by syamada           #+#    #+#             */
/*   Updated: 2018/08/14 08:49:56 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**convert_two(t_list *list)
{
	char	**input;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(list);
	input = (char **)malloc(sizeof(char *) * (len + 1));
	while (list)
	{
		input[i++] = ft_strdup(list->content);
		list = list->next;
	}
	return (input);
}

void		swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		partition(char **input, int left, int right)
{
	int		pivot;
	int		j;
	int		i;

	i = left;
	j = left;
	pivot = right;
	while (j < pivot)
	{
		while (ft_strcmp(input[j], input[pivot]) < 0)
			swap_str(&input[i++], &input[j]);
		j++;
	}
	swap_str(&input[i], &input[pivot]);
	return (i);
}

void	quick_sort(char ***input, int left, int right)
{
	int		pivot;

	pivot = partition(*input, left, right);

	quick_sort(input, left, pivot - 1);
	quick_sort(input, pivot + 1, right);
}
