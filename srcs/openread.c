/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 15:56:50 by syamada           #+#    #+#             */
/*   Updated: 2018/08/18 17:17:33 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static DIR		*open_dir(char *dirname)
{
	DIR		*dir;

	if (!(dir = opendir(dirname)))
	{
		open_error(dirname);
		return (NULL);
	}
	return (dir);
}

static void		recursiveopen(t_meta *data, int opts)
{
	struct stat st;
	t_meta		*tmp;

	tmp = NULL;
	while (data && MATCH(opts, CR))
	{
		stat(data->path, &st);
		if (ft_strequ(".", data->name) || ft_strequ("..", data->name)
				|| !MATCH(st.st_mode, S_IFDIR)
				|| (data->name[0] == '.' && !MATCH(opts, LA)))
		{
			data = data->next;
			continue ;
		}
		ft_printf("\n%s:\n", data->path);
		openread_dir(data->path, opts);
		data = data->next;
	}
}

void			openread_dir(char *dirname, int opts)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*path;
	t_meta			*data;

	data = NULL;
	if (!(dir = open_dir(dirname)))
		return ;
	while ((dp = readdir(dir)))
	{
		path = ft_strjoin_with(dirname, dp->d_name, '/');
		create_data(&data, dp->d_name, path);
		ft_strdel(&path);
	}
	data = dispatch_sort(&data, opts);
	print_dircontent(&data, opts);
	recursiveopen(data, opts);
	delete_alldata(&data, opts);
	ft_strdel(&dirname);
	closedir(dir);
}

void			get_file(char *filename, int opts)
{
	t_meta			*data;

	data = NULL;
	if (errno == ENOTDIR)
	{
		create_data(&data, filename, filename);
		if (MATCH(opts, LL))
		{
			data = get_metadata(data, opts);
			print_longformat(data, 1, 1);
			delete_data(&data, opts);
		}
		else
			ft_putendl(filename);
	}
	else
		open_error(filename);
}
