/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lformat_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:10:38 by syamada           #+#    #+#             */
/*   Updated: 2018/08/19 10:45:19 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		count_digit(int size)
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

static int		get_size_wd(t_meta *data, int opts)
{
	int		max;
	int		tmp;

	max = count_digit(data->size);
	while (data)
	{
		if (data->name[0] == '.' && !MATCH(opts, LA))
		{
			data = data->next;
			continue ;
		}
		if ((tmp = count_digit(data->size)) > max)
			max = tmp;
		data = data->next;
	}
	return (max);
}

static int		get_link_wd(t_meta *data, int opts)
{
	int		max;
	int		tmp;

	max = count_digit(data->n_links);
	while (data)
	{
		if (data->name[0] == '.' && !MATCH(opts, LA))
		{
			data = data->next;
			continue ;
		}
		if ((tmp = count_digit(data->n_links)) > max)
			max = tmp;
		data = data->next;
	}
	return (max);
}

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

void			lformat_handler(t_meta **data, int opts)
{
	int		width_size;
	int		width_link;
	int		blocks;
	t_meta	*d;

	blocks = get_sizelinkblock(data, opts);
	d = *data;
	width_size = get_size_wd(d, opts);
	width_link = get_link_wd(d, opts);
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
		d = get_metadata(d, opts);
		print_longformat(d, width_size, width_link);
		d = d->next;
	}
}
