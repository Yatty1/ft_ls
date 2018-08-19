/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lformat_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:10:38 by syamada           #+#    #+#             */
/*   Updated: 2018/08/19 16:21:05 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_sizelinkblock(t_meta **data, int opts)
{
	struct stat	st;
	t_meta		*d;
	int			blocks;

	d = *data;
	blocks = 0;
	while (d)
	{
		lstat(d->path, &st);
		d->size = st.st_size;
		d->n_links = st.st_nlink;
		blocks = d->name[0] == '.' && !MATCH(opts, LA) ?
			blocks : blocks + st.st_blocks;
		d = d->next;
	}
	return (blocks);
}

void			set_alldata(t_meta **data, int opts)
{
	t_meta	*d;

	d = *data;
	while (d)
	{
		if (d->name[0] == '.' && !MATCH(opts, LA))
		{
			d = d->next;
			continue ;
		}
		d = get_metadata(d, opts);
		d = d->next;
	}
}

void			get_width(t_meta **data, int opts, t_width *wd)
{
	t_meta	*d;

	d = *data;
	wd->usr = 1;
	wd->grp = 1;
	while (d)
	{
		if (d->name[0] == '.' && !MATCH(opts, LA))
		{
			d = d->next;
			continue ;
		}
		wd->usr = ft_strlen(d->owner) > wd->usr ?
			ft_strlen(d->owner) : wd->usr;
		wd->grp = ft_strlen(d->group) > wd->grp ?
			ft_strlen(d->group) : wd->grp;
		d = d->next;
	}
}

void			lformat_handler(t_meta **data, int opts)
{
	t_width	wd;
	int		blocks;
	t_meta	*d;

	blocks = get_sizelinkblock(data, opts);
	d = *data;
	wd.size = get_size_wd(d, opts);
	wd.link = get_link_wd(d, opts);
	ft_putstr("total ");
	ft_putnbr(blocks);
	ft_putchar('\n');
	set_alldata(data, opts);
	get_width(data, opts, &wd);
	while (d)
	{
		if (d->name[0] == '.' && !MATCH(opts, LA))
		{
			d = d->next;
			continue ;
		}
		print_longformat(d, wd);
		d = d->next;
	}
}
