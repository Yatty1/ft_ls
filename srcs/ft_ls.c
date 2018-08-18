/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:26 by syamada           #+#    #+#             */
/*   Updated: 2018/08/17 13:41:26 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

DIR		*open_dir(char *dirname)
{
	DIR		*dir;

	if (!(dir = opendir(dirname)))
	{
		ft_printf("./ft_ls: %s %s", dirname, strerror(errno));
		return (NULL);
	}
	return (dir);
}

void	openread_dir(char *dirname, int opts)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat		st;
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
	while (data && MATCH(opts, CR))
	{
		stat(data->path, &st);
		if (ft_strequ(".", data->name) || ft_strequ("..", data->name)
				|| !MATCH(st.st_mode, S_IFDIR))
		{
			data = data->next;
			continue ;
		}
		ft_printf("\n%s:\n", data->path);
		openread_dir(data->path, opts);
		data = data->next;
	}
	closedir(dir);
}

void	get_file(char *filename, int opts)
{
	t_meta			*data;

	create_data(&data, filename, filename);
	if (errno == ENOTDIR)
	{
		if (MATCH(opts, LL))
		{
			data = get_metadata(data, opts);
			ft_printf("%s  %d %s  %s  %d %s %s\n", data->mode, data->n_links,
					data->owner, data->group, data->size, ft_strsub(ctime(&data->m_time), 4, 12), filename);
		}
		else
			ft_putendl(filename);
	}
}

int		main(int argc, char **argv)
{
	DIR				*dir;
	int				opts;
	int				i;

	i = 1;
	argv = check_option(&argc, argv, &opts);
	if (argc == 1)
		openread_dir(ft_strdup("."), opts);
	while (argv[i])
	{
		if (!(dir = opendir(argv[i])))
			get_file(ft_strdup(argv[i++]), opts);
		else
			openread_dir(ft_strdup(argv[i++]), opts);
	}
	return (0);
}
