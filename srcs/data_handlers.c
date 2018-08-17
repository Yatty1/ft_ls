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

static int	count_digit(long size)
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

static int max(t_meta *data)
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

void		lformat_handler(t_meta **data, int opts)
{
	int		width;

	width = max(*data);
	while (*data)
	{
		if ((*data)->name[0] == '.' && !MATCH(opts, LA))
		{
			(*data) = (*data)->next;
			continue ;
		}
		*data = get_metadata(*data, opts);
		print_longformat(*data, width);
		(*data) = (*data)->next;
	}
}

void		time_handler(t_meta **data, int opts)
{
	while (*data)
	{
		if ((*data)->name[0] == '.' && !MATCH(opts, LA))
		{
			(*data) = (*data)->next;
			continue ;
		}
		ft_putendl((*data)->name);
		(*data) = (*data)->next;
	}
}
