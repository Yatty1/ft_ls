/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:49:14 by syamada           #+#    #+#             */
/*   Updated: 2018/08/17 13:37:34 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*time_determine(time_t t)
{
	time_t	curr;
	char	*str;

	time(&curr);
	if ((curr - t) < HALF_A_YEAR)
		str = ft_strsub(ctime(&t), 4, 12);
	else
	{
		str = ft_strsub(ctime(&t), 4, 7);
		str = ft_strjoinfree(str, ft_strsub(ctime(&t), 20, 4));
	}
	return (str);
}


void		print_longformat(t_meta *data, int width_size, int width_link)
{
	char	*time;

	/*
	ft_putstr(data->mode);
	ft_putstr("  ");
	ft_putnbr((int)data->n_links);
	ft_putstr(" ");
	ft_putstr(data->owner);
	ft_putstr(" ");
	ft_putstr(data->group);
	ft_putstr("  ");
	ft_putnbr((int)data->size);
	ft_putstr(" ");
	time = time_determine(data->m_time);
	ft_putstr(time);
	ft_putchar(' ');
	ft_putendl(data->name);
	*/
	time = time_determine(data->m_time);
	if (data->mode[0] == 'l')
	{

		ft_printf("%s  %*d %s  %s  %*d %s %s -> %s\n", data->mode, width_link, data->n_links,
			data->owner, data->group, width_size, data->size, time, data->name, data->symlink);
	}
	else
	{
		ft_printf("%s  %*d %s  %s  %*d %s %s\n", data->mode, width_link, data->n_links,
			data->owner, data->group, width_size, data->size, time, data->name);
	}
	ft_strdel(&time);
}

void		print_dircontent(t_meta **data, int opts)
{
	t_meta		*d;
	struct stat	st;

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
//	else if (MATCH(opts, LT))
//		time_handler(data, opts);
//	if (MATCH(opts, CR) && !MATCH(opts, LL))
}
