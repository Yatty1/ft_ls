/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:00:07 by syamada           #+#    #+#             */
/*   Updated: 2018/08/18 17:12:49 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		create_data(t_meta **data, char *name, char *path)
{
	t_meta	*new;

	new = (t_meta *)malloc(sizeof(t_meta));
	new->name = ft_strdup(name);
	new->path = ft_strdup(path);
	new->mode = NULL;
	new->owner = NULL;
	new->group = NULL;
	new->date = NULL;
	new->symlink = NULL;
	new->next = NULL;
	if (!*data)
	{
		*data = new;
		return ;
	}
	new->next = *data;
	*data = new;
}

void		delete_data(t_meta **data, int opts)
{
	t_meta	*d;

	d = *data;
	if (d->name[0] == '.' && !MATCH(opts, LA))
	{
		ft_strdel(&d->name);
		ft_strdel(&d->path);
		return ;
	}
	ft_strdel(&d->mode);
	ft_strdel(&d->owner);
	ft_strdel(&d->group);
	ft_strdel(&d->date);
	ft_strdel(&d->time);
	ft_strdel(&d->name);
	ft_strdel(&d->symlink);
	ft_strdel(&d->path);
}

void		delete_alldata(t_meta **data, int opts)
{
	t_meta	*d;
	t_meta	*tmp;

	d = *data;
	while (d)
	{
		delete_data(&d, opts);
		tmp = d;
		d = d->next;
		free(tmp);
	}
	*data = NULL;
}
