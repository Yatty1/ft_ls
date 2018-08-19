/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:29:21 by syamada           #+#    #+#             */
/*   Updated: 2018/08/19 11:28:45 by syamada          ###   ########.fr       */
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
	struct stat		st;
	struct passwd	*pd;
	struct group	*gr;

	lstat(data->path, &st);
	data = get_mode(st, data);
	data->n_links = st.st_nlink;
	data->owner = ft_strdup(getpwuid(st.st_uid)->pw_name);
	data->group = ft_strdup(getgrgid(st.st_gid)->gr_name);
	/*
	if (!(pd = getpwuid(st.st_uid)))
		data->owner = ft_strdup(pd->pw_name);
	else
		data->owner = ft_ltoa(st.st_uid);
	if (!(gr = getgrgid(st.st_gid)))
		data->group = ft_strdup(gr->gr_name);
	else
		data->group = ft_ltoa(st.st_uid);
		*/
	data->size = st.st_size;
	data->m_time = st.st_mtime;
	data->symlink = get_symlink(st, data);
	data->major = MAJOR(st.st_rdev);
	data->minor = MINOR(st.st_rdev);
	return (data);
}
