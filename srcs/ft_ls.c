/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:26 by syamada           #+#    #+#             */
/*   Updated: 2018/08/13 13:20:03 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	openread_dir(char *dirname, int is_first)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat 	buf;
	char			*path;
	t_list			*dirlist;

	dirlist = NULL;
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
		if ((buf.st_mode & S_IFREG) == S_IFREG)
			ft_printf("reg: %s\n", dp->d_name);
		else if ((buf.st_mode & S_IFDIR) == S_IFDIR)
		{
			if (ft_strequ(".", dp->d_name) || ft_strequ("..", dp->d_name))
			{
				ft_printf("dir: %s\n", dp->d_name);
				continue ;
			}
			ft_printf("%s\n", dp->d_name);
			ft_lstadd(&dirlist, ft_lstnew(path, ft_strlen(path)));
		}
	}
	ft_printlist(dirlist);
	/*
	while (dirlist)
	{
		openread_dir(dirlist->content, 1);
		dirlist = dirlist->next;
	}
	*/
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
		openread_dir(ft_strdup("."), 1);
	while (argv[i])
		openread_dir(ft_strdup(argv[i++]), 1);
	return (0);
}