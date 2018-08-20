/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:29:21 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 15:20:38 by syamada          ###   ########.fr       */
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
	struct passwd	*pd;
	struct group	*gr;

	data = get_mode(data->st, data);
	if ((pd = getpwuid(data->st.st_uid)))
		data->owner = ft_strdup(pd->pw_name);
	else
		data->owner = ft_lltoa(data->st.st_uid);
	if ((gr = getgrgid(data->st.st_gid)))
		data->group = ft_strdup(gr->gr_name);
	else
		data->group = ft_lltoa(data->st.st_uid);
	data->symlink = get_symlink(data->st, data);
	data->major = MAJOR(data->st.st_rdev);
	data->minor = MINOR(data->st.st_rdev);
	return (data);
}
