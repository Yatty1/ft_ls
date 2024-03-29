/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 15:56:50 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 15:21:57 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static DIR		*open_dir(char *dirname, int opts)
{
	DIR		*dir;

	if (!(dir = opendir(dirname)))
	{
		get_file(dirname, opts);
		return (NULL);
	}
	return (dir);
}

static void		recursiveopen(t_meta *data, int opts)
{
	char		*dirname;

	while (data && MATCH(opts, CR))
	{
		if (ft_strequ(".", data->name) || ft_strequ("..", data->name)
				|| !MATCH(data->st.st_mode, S_IFDIR)
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
	if (!(dir = open_dir(dirname, opts)))
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
	closedir(dir);
}

void			get_file(char *filename, int opts)
{
	t_meta			*data;
	t_width			wd;

	data = NULL;
	wd.size = 1;
	wd.link = 1;
	wd.usr = 1;
	wd.grp = 1;
	if (errno == ENOTDIR)
	{
		if (MATCH(opts, LL))
		{
			create_data(&data, filename, filename);
			data = get_metadata(data, opts);
			print_longformat(data, wd, opts);
			delete_data(&data, opts);
		}
		else
			ft_putendl(filename);
	}
	else
		open_error(filename);
}
