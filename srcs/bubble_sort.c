/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 16:29:38 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 23:20:02 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		cpy_data(t_meta **dest, t_meta *src)
{
	t_meta	*data;

	data = *dest;
	data->mode = src->mode;
	data->n_links = src->n_links;
	data->owner = src->owner;
	data->group = src->group;
	data->size = src->size;
	data->m_time = src->m_time;
	data->name = src->name;
	//don't forget symlink
	data->path = src->path;
}

void		swap_data(t_meta **first, t_meta **second)
{
	t_meta	tmp;

	tmp = **first;
	cpy_data(first, *second);
	cpy_data(second, &tmp);
}

t_meta		*bubble_sort(t_meta	**data, int is_asc)
{
	t_meta	*f;
	t_meta	*s;

	f = *data;
	while (f)
	{
		s = *data;
		while (s->next)
		{
			if (is_asc ? ft_strcmp(s->name, s->next->name) > 0
					: ft_strcmp(s->name, s->next->name) < 0)
				swap_data(&s, &s->next);
			s = s->next;
		}
		f = f->next;
	}
	return (*data);
}
