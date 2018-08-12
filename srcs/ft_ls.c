/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:26 by syamada           #+#    #+#             */
/*   Updated: 2018/08/12 14:49:38 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	openread_dir(char *dirname)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat 	buf;
	char			*path;

	if (!(dir = opendir(dirname)))
	{
		//call stat to take info if it's file with flag -l
		//error: no permission, not existing
		ft_printf("./ft_ls: %s: %s\n", dirname, strerror(errno));
		return ;
	}
	while ((dp = readdir(dir)))
	{
		path = ft_strjoin_with(dirname, dp->d_name, '/');
		stat(path, &buf);
		ft_printf("%s, %d\n", dp->d_name, buf.st_size);
		ft_strdel(&path);
		/*
		path = ft_strjoin_with(filename, dp->d_name, '/');
		ft_strdel(&filename);
		stat(path, &buf);
		if (buf.st_mode & S_IFREG)
		{
			if (ft_strequ(".", dp->d_name) || ft_strequ("..", dp->d_name))
			{
				ft_printf("dir: %s\n", dp->d_name);
				continue ;
			}
			ft_printf("reg: %s\n", dp->d_name);
		}
		else if (buf.st_mode & S_IFDIR)
		{
			ft_printf("%s:\n", path);
			openread_dir(path);
		}
		*/
	}
	closedir(dir);
}

int		main(int argc, char **argv)
{
	DIR				*dir;
	t_options		opts;
	int				i;

	i = 1;
	argv = check_option(&argc, argv, &opts);
	if (argc == 1)
		openread_dir(ft_strdup("."));
	while (argv[i])
		openread_dir(ft_strdup(argv[i++]));
	return (0);
}
