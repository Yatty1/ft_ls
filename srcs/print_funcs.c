/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:49:14 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 22:56:46 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_longformat(t_meta *data)
{
	char	*time;

	ft_putstr(data->mode);
	ft_putstr("  ");
	ft_putnbr((int)data->n_links);
	ft_putstr(" ");
	ft_putstr(data->owner);
	ft_putstr(" ");
	ft_putstr(data->group);
	ft_putstr("  ");
	ft_putnbr((int)data->n_links);
	ft_putstr(" ");
	time = ctime(&data->m_time);
	ft_putstr(time);
	ft_putendl(data->name);
}

void		print_dircontent(t_meta *data)
{
	while (data)
	{
		ft_putendl(data->name);
		data = data->next;
	}
}
