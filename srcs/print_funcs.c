/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:49:14 by syamada           #+#    #+#             */
/*   Updated: 2018/08/19 11:50:25 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		time_determine(t_meta **data)
{
	time_t	curr;
	char	*str;

	time(&curr);
	str = ctime(&(*data)->m_time);
	(*data)->date = ft_strsub(str, 4, 6);
	if ((curr - (*data)->m_time) < HALF_A_YEAR)
		(*data)->time = ft_strsub(str, 11, 5);
	else
		(*data)->time = ft_strsub(str, 20, 4);
}

void			print_longformat(t_meta *data, int width_size, int width_link)
{
	time_determine(&data);
	if (data->mode[0] == 'l')
	{
		ft_printf("%s  %*d %s  %s  %*d %s %*s %s -> %s\n",
				data->mode, width_link, data->n_links, data->owner, data->group,
				width_size, data->size, data->date, 5, data->time, data->name,
				data->symlink);
	}
	else if (data->mode[0] == 'c' || data->mode[0] == 'b')
	{
		ft_printf("%s  %*d %s  %s  %*d, %*d %s %*s %s\n",
				data->mode, width_link, data->n_links, data->owner, data->group,
				width_size, data->major, width_size, data->minor, data->date, 5,
				data->time, data->name);
	}
	else
	{
		ft_printf("%s  %*d %s  %s  %*d %s %*s %s\n",
				data->mode, width_link, data->n_links, data->owner, data->group,
				width_size, data->size, data->date, 5, data->time, data->name);
	}
}

void			print_dircontent(t_meta **data, int opts)
{
	t_meta		*d;

	d = *data;
	while (d && !(opts & LL))
	{
		if (d->name[0] == '.' && !MATCH(opts, LA))
		{
			d = d->next;
			continue ;
		}
		ft_putendl(d->name);
		d = d->next;
	}
	if (MATCH(opts, LL))
		lformat_handler(data, opts);
}
