/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 13:04:11 by syamada           #+#    #+#             */
/*   Updated: 2018/08/19 17:00:06 by syamada          ###   ########.fr       */
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

int				get_size_wd(t_meta *data, int opts)
{
	int		max;
	int		tmp;

	max = count_digit(data->st.st_size);
	while (data)
	{
		if (data->name[0] == '.' && !MATCH(opts, LA))
		{
			data = data->next;
			continue ;
		}
		if ((tmp = count_digit(data->st.st_size)) > max)
			max = tmp;
		data = data->next;
	}
	return (max);
}

int				get_link_wd(t_meta *data, int opts)
{
	int		max;
	int		tmp;

	max = count_digit(data->st.st_nlink);
	while (data)
	{
		if (data->name[0] == '.' && !MATCH(opts, LA))
		{
			data = data->next;
			continue ;
		}
		if ((tmp = count_digit(data->st.st_nlink)) > max)
			max = tmp;
		data = data->next;
	}
	return (max);
}

int				get_usr_wd(t_meta *data, int opts)
{
	int		max;
	int		tmp;

	max = ft_strlen(data->owner);
	while (data)
	{
		if (data->name[0] == '.' && !MATCH(opts, LA))
		{
			data = data->next;
			continue ;
		}
		if ((tmp = ft_strlen(data->owner)) > max)
			max = tmp;
		data = data->next;
	}
	return (max);
}

int				get_group_wd(t_meta *data, int opts)
{
	int		max;
	int		tmp;

	max = ft_strlen(data->group);
	while (data)
	{
		if (data->name[0] == '.' && !MATCH(opts, LA))
		{
			data = data->next;
			continue ;
		}
		if ((tmp = ft_strlen(data->group)) > max)
			max = tmp;
		data = data->next;
	}
	return (max);
}
