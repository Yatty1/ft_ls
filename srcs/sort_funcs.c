/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 07:48:59 by syamada           #+#    #+#             */
/*   Updated: 2018/08/14 20:59:22 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**convert_two(t_list *list)
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

void			quick_sort(char ***input, int left, int right, int is_asc)
{
	int		pivot;

	if (left >= right)
		return ;
	pivot = partition(*input, left, right, is_asc);
	quick_sort(input, left, pivot - 1, is_asc);
	quick_sort(input, pivot + 1, right, is_asc);
}

void			sort_content(t_list *list, int is_asc)
{
	char	**input;

	input = convert_two(list);
	quick_sort(&input, 0, ft_lstsize(list) - 1, is_asc);
}

/*
int		main()
{
	t_list	*list;
	char	**input;

	list = 0;
	ft_lstpush(&list, "ddd", 3);
	ft_lstpush(&list, "aaa", 3);
	ft_lstpush(&list, "hhh", 3);
	ft_lstpush(&list, "ccc", 3);
	ft_lstpush(&list, "ggg", 3);
	ft_lstpush(&list, "bbb", 3);
	ft_lstpush(&list, "eee", 3);
	ft_lstpush(&list, "fff", 3);
	input = convert_two(list);
	quick_sort(&input, 0, ft_lstsize(list) - 1);
	int i = 0;
	while (i < ft_lstsize(list))
	{
		ft_printf("%d: %s\n", i, input[i]);
		i++;
	}
	return (0);
}
*/
