/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lformat_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:10:38 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 15:20:40 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		count_digit(size_t size)
{
	int		i;

	i = 0;
	while (size)
	{
		size /= 10;
		i++;
	}
	return (i);
}

long			set_alldata(t_meta **data, int opts, t_width *wd)
{
	t_meta	*d;
	long	blocks;

	d = *data;
	blocks = 0;
	while (d)
	{
		if (d->name[0] == '.' && !MATCH(opts, LA))
		{
			d = d->next;
			continue ;
		}
		d = get_metadata(d, opts);
		blocks += d->st.st_blocks;
		wd->usr = ft_strlen(d->owner) > wd->usr ?
			ft_strlen(d->owner) : wd->usr;
		wd->grp = ft_strlen(d->group) > wd->grp ?
			ft_strlen(d->group) : wd->grp;
		wd->size = count_digit(d->st.st_size) > wd->size ?
			count_digit(d->st.st_size) : wd->size;
		wd->link = count_digit(d->st.st_nlink) > wd->link ?
			count_digit(d->st.st_nlink) : wd->link;
		d = d->next;
	}
	return (blocks);
}

void			lformat_handler(t_meta **data, int opts)
{
	t_width		wd;
	long		blocks;
	t_meta		*d;

	d = *data;
	wd.link = 1;
	wd.size = 1;
	wd.usr = 1;
	wd.grp = 1;
	blocks = set_alldata(data, opts, &wd);
	ft_putstr("total ");
	ft_putnbr(blocks);
	ft_putchar('\n');
	while (d)
	{
		if (d->name[0] == '.' && !MATCH(opts, LA))
		{
			d = d->next;
			continue ;
		}
		print_longformat(d, wd, opts);
		d = d->next;
	}
}
