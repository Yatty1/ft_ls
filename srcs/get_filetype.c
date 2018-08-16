/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filetype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 13:31:37 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 16:10:56 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		get_filetype(struct stat st)
{
	if (MATCH(st.st_mode, S_IFREG))
		return ('-');
	else if (MATCH(st.st_mode, S_IFDIR))
		return ('d');
	else if (MATCH(st.st_mode, S_IFCHR))
		return ('c');
	else if (MATCH(st.st_mode, S_IFBLK))
		return ('b');
	else if (MATCH(st.st_mode, S_IFIFO))
		return ('p');
	else if (MATCH(st.st_mode, S_IFLNK))
		return ('l');
	else if (MATCH(st.st_mode, S_IFSOCK))
		return ('s');
	return (' ');
}

char		get_execpermit(struct stat st)
{
	if (MATCH(st.st_mode, (S_IXUSR | S_IXGRP | S_IXOTH)))
		return ('x');
	if (MATCH(st.st_mode, (S_ISUID | S_ISGID)))
		return ('s');
	if (MATCH(st.st_mode, S_ISVTX))
		return ('t');
	return ('-');
}

t_meta		*get_mode(struct stat st, t_meta *data)
{
	data->mode = ft_strnew(10);
	data->mode[0] = get_filetype(st);
	data->mode[1] = MATCH(st.st_mode, S_IRUSR) ? 'r' : '-';
	data->mode[2] = MATCH(st.st_mode, S_IWUSR) ? 'w' : '-';
	data->mode[3] = get_execpermit(st);
	data->mode[4] = MATCH(st.st_mode, S_IRGRP) ? 'r' : '-';
	data->mode[5] = MATCH(st.st_mode, S_IWGRP) ? 'w' : '-';
	data->mode[6] = get_execpermit(st);
	data->mode[7] = MATCH(st.st_mode, S_IROTH) ? 'r' : '-';
	data->mode[8] = MATCH(st.st_mode, S_IWOTH) ? 'w' : '-';
	data->mode[9] = get_execpermit(st);
	return (data);
}

