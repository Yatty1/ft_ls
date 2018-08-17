/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:00:07 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 23:11:39 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		create_data(t_meta **data, char *name, char *path)
{
	t_meta	*new;

	new = (t_meta *)malloc(sizeof(t_meta));
	new->name = ft_strdup(name);
	new->path = ft_strdup(path);
	new->next = NULL;
	if (!*data)
	{
		*data = new;
		return ;
	}
	new->next = *data;
	*data = new;
}
