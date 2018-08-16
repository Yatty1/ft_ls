/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 16:29:38 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 16:35:51 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*bubble_sort(t_list	**blist, int is_asc)
{
	int		len;
	int		i;
	void	*tmp;
	t_list	*list;

	i = 0;
	len = ft_lstsize(*blist);
	while (len)
	{
		list = *blist;
		while (i < len)
		{
			tmp = list->content;
			if (is_asc ? ft_strcmp(list->content, list->next->content) > 0
					: ft_strcmp(list->content, list->next->content) < 0)
			{
				list->content = list->next->content;
				list->next->content = tmp;
			}
			list = list->next;
			i++;
		}
		len--;
	}
	return (list);
}
