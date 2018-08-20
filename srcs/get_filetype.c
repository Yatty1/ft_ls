/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filetype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 13:31:37 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 11:10:23 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		get_filetype(struct stat st)
{
	if (MATCH(st.st_mode, S_IFLNK))
		return ('l');
	if (MATCH(st.st_mode, S_IFCHR))
		return ('c');
	if (MATCH(st.st_mode, S_IFBLK))
		return ('b');
	if (MATCH(st.st_mode, S_IFIFO))
		return ('p');
	if (MATCH(st.st_mode, S_IFSOCK))
		return ('s');
	if (MATCH(st.st_mode, S_IFDIR))
		return ('d');
	if (MATCH(st.st_mode, S_IFREG))
		return ('-');
	return (' ');
}

static char		get_usrexepermit(struct stat st)
{
	if (MATCH(st.st_mode, (S_IXUSR | S_ISUID)))
		return ('s');
	if (MATCH(st.st_mode, (S_ISUID)))
		return ('S');
	if (MATCH(st.st_mode, S_IXUSR))
		return ('x');
	return ('-');
}

static char		get_grpexepermit(struct stat st)
{
	if (MATCH(st.st_mode, (S_IXGRP | S_ISGID)))
		return ('s');
	if (MATCH(st.st_mode, (S_ISGID)))
		return ('S');
	if (MATCH(st.st_mode, S_IXGRP))
		return ('x');
	return ('-');
}

static char		get_othexepermit(struct stat st)
{
	if (MATCH(st.st_mode, (S_IXOTH | S_ISVTX)))
		return ('t');
	if (MATCH(st.st_mode, (S_ISVTX)))
		return ('T');
	if (MATCH(st.st_mode, S_IXOTH))
		return ('x');
	return ('-');
}

t_meta			*get_mode(struct stat st, t_meta *data)
{
	data->mode = ft_strnew(11);
	data->mode[0] = get_filetype(st);
	data->mode[1] = MATCH(st.st_mode, S_IRUSR) ? 'r' : '-';
	data->mode[2] = MATCH(st.st_mode, S_IWUSR) ? 'w' : '-';
	data->mode[3] = get_usrexepermit(st);
	data->mode[4] = MATCH(st.st_mode, S_IRGRP) ? 'r' : '-';
	data->mode[5] = MATCH(st.st_mode, S_IWGRP) ? 'w' : '-';
	data->mode[6] = get_grpexepermit(st);
	data->mode[7] = MATCH(st.st_mode, S_IROTH) ? 'r' : '-';
	data->mode[8] = MATCH(st.st_mode, S_IWOTH) ? 'w' : '-';
	data->mode[9] = get_othexepermit(st);
	data->mode[10] = get_attributes(st, data->path);
	return (data);
}
