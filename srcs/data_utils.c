/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:00:07 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 14:42:58 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		create_data(t_meta **data, char *name, char *path)
{
	t_meta		*new;
	struct stat	st;

	if (lstat(path, &st) < 0)
		open_error(path);
	new = (t_meta *)malloc(sizeof(t_meta));
	new->name = ft_strdup(name);
	new->path = ft_strdup(path);
	new->mode = NULL;
	new->owner = NULL;
	new->group = NULL;
	new->date = NULL;
	new->time = NULL;
	new->symlink = NULL;
	new->st = st;
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
	ft_strdel(&(*data)->mode);
	ft_strdel(&(*data)->owner);
	ft_strdel(&(*data)->group);
	ft_strdel(&(*data)->date);
	ft_strdel(&(*data)->time);
	ft_strdel(&(*data)->name);
	ft_strdel(&(*data)->symlink);
	ft_strdel(&(*data)->path);
	free(*data);
	*data = NULL;
}

void		delete_alldata(t_meta **data, int opts)
{
	t_meta	*tmp;

	while ((*data))
	{
		tmp = (*data)->next;
		delete_data(&*data, opts);
		(*data) = tmp;
	}
	*data = NULL;
}

void		delete_input(char **input)
{
	int		i;

	i = 0;
	while (input[i])
		ft_strdel(&input[i++]);
}
