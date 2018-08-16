/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:29:21 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 16:22:09 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_meta		*get_metadata(struct stat st, t_meta *data, t_options opts)
{
	data = get_mode(st, data);
	data->n_links = st.st_nlink;
	data->owner = getpwuid(st.st_uid)->pw_name;
	data->group = getgrgid(st.st_gid)->gr_name;
	data->size = st.st_size;
	data->m_time = st.st_mtime;
	return (data);
}
