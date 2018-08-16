/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:26 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 16:23:32 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	openread_dir(char *dirname, t_options opts)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat 	buf;
	char			*path;
	t_list			*dirlist;
	t_list			*dircontent;
	char			**input;

	dirlist = NULL;
	dircontent = NULL;
	if (!(dir = opendir(dirname)))
	{
		ft_printf("./ft_ls: %s: %s\n", dirname, strerror(errno));
		return ;
	}
	while ((dp = readdir(dir)))
	{
		path = ft_strjoin_with(dirname, dp->d_name, '/');
		stat(path, &buf);
		if (MATCH(buf.st_mode, S_IFREG))
			ft_lstadd(&dircontent, ft_lstnew(dp->d_name, ft_strlen(dp->d_name)));
		else if (MATCH(buf.st_mode, S_IFDIR))
		{
			if (dp->d_name[0] == '.')
			{
				if (opts.a)
					ft_lstadd(&dircontent, ft_lstnew(dp->d_name, ft_strlen(dp->d_name)));
				continue ;
			}
			ft_lstadd(&dircontent, ft_lstnew(dp->d_name, ft_strlen(dp->d_name)));
			ft_lstadd(&dirlist, ft_lstnew(path, ft_strlen(path)));
		}
		ft_strdel(&path);
	}
	input = sort_content(dircontent, !opts.r);
	while (*input)
		ft_putendl(*input++);
	while (dirlist && opts.c_r)
	{
		ft_printf("\n%s:\n", (char *)dirlist->content);
		openread_dir(dirlist->content, opts);
		dirlist = dirlist->next;
	}
	closedir(dir);
}

void	get_file(char *filename, t_options opts)
{
	struct stat		buf;
	t_meta			*data;

	data = (t_meta *)malloc(sizeof(t_meta));
	if (errno == ENOTDIR)
	{
		stat(filename, &buf);
		if (opts.l)
		{
			data = get_metadata(buf, data, opts);
			data->name = filename;
			ft_printf("%s  %d %s  %s  %d %s %s\n", data->mode, data->n_links,
					data->owner, data->group, data->size, ft_strsub(ctime(&data->m_time), 4, 12), data->name);
		}
		else
			ft_putendl(filename);
	}
}

int		main(int argc, char **argv)
{
	DIR				*dir;
	t_options		opts;
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
