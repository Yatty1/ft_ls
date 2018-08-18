/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 10:33:19 by syamada           #+#    #+#             */
/*   Updated: 2018/08/18 10:37:34 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		get_time(t_meta **data)
{
	struct stat	st;
	t_meta	*d;

	d = *data;
	while (d)
	{
		stat(d->path, &st);
		d->m_time = st.st_mtime;
		d = d->next;
	}
}

t_meta			*dispatch_sort(t_meta **data, int opts)
{
	if (MATCH(opts, LT))
	{
		get_time(data);
		return (time_sort(data));
	}
	return (bubble_sort(data, !MATCH(opts, LR)));
}
