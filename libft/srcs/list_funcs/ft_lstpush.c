/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:15:25 by syamada           #+#    #+#             */
/*   Updated: 2018/08/07 11:58:34 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **alst, void *content, size_t size)
{
	t_list	*list;

	if (alst == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = ft_lstnew(content, size);
		return ;
	}
	list = *alst;
	while (list->next)
		list = list->next;
	list->next = ft_lstnew(content, size);
}
