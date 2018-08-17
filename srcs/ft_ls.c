/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:26 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 23:22:24 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	openread_dir(char *dirname, int opts)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat		buf;
	char			*path;
	t_meta			*data;

	data = NULL;
	if (!(dir = opendir(dirname)))
	{
		ft_printf("./ft_ls: %s: %s\n", dirname, strerror(errno));
		return ;
	}
	while ((dp = readdir(dir)))
	{
		path = ft_strjoin_with(dirname, dp->d_name, '/');
		stat(path, &buf);
		create_data(&data, dp->d_name, path);
		data = get_metadata(buf, data, opts);
		ft_strdel(&path);
	}
	data = bubble_sort(&data, !MATCH(opts, LR));
	print_dircontent(data);
	while (data && MATCH(opts, CR))
	{
		if (ft_strequ(".", data->name) || ft_strequ("..", data->name)
				|| data->mode[0] != 'd')
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
	struct stat		buf;
	t_meta			*data;

	data = (t_meta *)malloc(sizeof(t_meta));
	if (errno == ENOTDIR)
	{
		stat(filename, &buf);
		if (MATCH(opts, LA))
		{
			data = get_metadata(buf, data, opts);
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
