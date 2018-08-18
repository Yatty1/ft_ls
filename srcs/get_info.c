/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:29:21 by syamada           #+#    #+#             */
/*   Updated: 2018/08/18 12:35:54 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*get_symlink(struct stat st, t_meta *data)
{
	char	buf[101];
	int		ret;

	if (MATCH(st.st_mode, S_IFLNK))
	{
		ret = readlink(data->path, buf, 100);
		buf[ret] = '\0';
		return (ft_strdup(buf));
	}
	return (ft_strdup(""));
}

t_meta			*get_metadata(t_meta *data, int opts)
{
	struct stat	st;

	lstat(data->path, &st);
	data = get_mode(st, data);
	data->n_links = st.st_nlink;
	data->owner = getpwuid(st.st_uid)->pw_name;
	data->group = getgrgid(st.st_gid)->gr_name;
	data->size = st.st_size;
	data->m_time = st.st_mtime;
	data->symlink = get_symlink(st, data);
	data->major = MAJOR(st.st_rdev);
	data->minor = MINOR(st.st_rdev);
	return (data);
}
