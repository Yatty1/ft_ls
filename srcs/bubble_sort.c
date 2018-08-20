/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 16:29:38 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 11:09:20 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		cpy_data(t_meta **dest, t_meta *src)
{
	t_meta	*data;

	data = *dest;
	data->name = src->name;
	data->path = src->path;
	data->st = src->st;
}

static void		swap_data(t_meta **first, t_meta **second)
{
	t_meta	tmp;

	tmp = **first;
	cpy_data(first, *second);
	cpy_data(second, &tmp);
}

t_meta			*time_sort(t_meta **data)
{
	t_meta	*f;
	t_meta	*s;

	f = *data;
	while (f)
	{
		s = *data;
		while (s->next)
		{
			if (s->st.st_mtime < s->next->st.st_mtime)
				swap_data(&s, &s->next);
			s = s->next;
		}
		f = f->next;
	}
	return (*data);
}

t_meta			*bubble_sort(t_meta **data, int is_asc)
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
