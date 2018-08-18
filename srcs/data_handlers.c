/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 11:24:44 by syamada           #+#    #+#             */
/*   Updated: 2018/08/17 13:38:09 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	count_digit(int size)
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

static int	get_size_wd(t_meta *data)
{
	int		max;
	int		tmp;

	max = count_digit(data->size);
	while (data)
	{
		if ((tmp = count_digit(data->size)) > max)
			max = tmp;
		data = data->next;
	}
	return (max);
}

static int	get_link_wd(t_meta *data)
{
	int		max;
	int		tmp;

	max = count_digit(data->n_links);
	while (data)
	{
		if ((tmp = count_digit(data->n_links)) > max)
			max = tmp;
		data = data->next;
	}
	return (max);
}

t_meta		*get_size_link(t_meta *data)
{
	struct stat	st;
	t_meta		*d;

	d = data;
	while (d)
	{
		stat(d->path, &st);
		d->size = st.st_size;
		d->n_links = st.st_nlink;
		d = d->next;
	}
	return (data);
}

void		lformat_handler(t_meta **data, int opts)
{
	int		width_size;
	int		width_link;
	t_meta	*d;

	d = get_size_link(*data);
	width_size = get_size_wd(d);
	width_link = get_link_wd(d);
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
