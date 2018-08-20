/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:49:14 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 15:51:35 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		time_determine(t_meta **data)
{
	time_t	curr;
	char	*str;

	time(&curr);
	str = ctime(&(*data)->st.st_mtime);
	(*data)->date = ft_strsub(str, 4, 6);
	if ((curr - (*data)->st.st_mtime) < HALF_A_YEAR)
		(*data)->time = ft_strsub(str, 11, 5);
	else
		(*data)->time = ft_strsub(str, 20, 4);
}

static void		color_print(t_meta *data, int opts)
{
	if (MATCH(opts, CG))
	{
		if (data->st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
			ft_putstr("\033[31m");
		if (MATCH(data->st.st_mode, S_IFDIR))
			ft_putstr("\033[34m");
		if (MATCH(data->st.st_mode, S_IFCHR))
			ft_putstr("\033[34;1m");
		if (MATCH(data->st.st_mode, S_IFIFO))
			ft_putstr("\033[33m");
		if (MATCH(data->st.st_mode, S_IFSOCK))
			ft_putstr("\033[32m");
	}
	ft_putendl(data->name);
	ft_putstr("\033[m");
}

void			print_longformat(t_meta *data, t_width wd, int opts)
{
	time_determine(&data);
	if (data->mode[0] == 'l')
	{
		ft_printf("%s %*d %-*s  %-*s  %*D %s %*s ", data->mode, wd.link,
				data->st.st_nlink, wd.usr, data->owner, wd.grp, data->group,
				wd.size, data->st.st_size, data->date, 5, data->time);
		ft_printf(MATCH(opts, CG) ? "\033[35m%s \033[m -> %s\n" : "%s -> %s\n",
				data->name, data->symlink);
	}
	else if (data->mode[0] == 'b' || data->mode[0] == 'c')
	{
		ft_printf("%s %*d %-*s  %-*s  %*d, %*d %s %*s ", data->mode,
				wd.link, data->st.st_nlink, wd.usr, data->owner, wd.grp,
				data->group, wd.major, data->major, wd.minor, data->minor,
				data->date, 5, data->time);
		color_print(data, opts);
	}
	else
	{
		ft_printf("%s %*d %-*s  %-*s  %*D %s %*s ",
				data->mode, wd.link, data->st.st_nlink, wd.usr, data->owner,
				wd.grp, data->group, wd.size, data->st.st_size, data->date,
				5, data->time);
		color_print(data, opts);
	}
}

void			print_dircontent(t_meta **data, int opts)
{
	t_meta		*d;

	d = *data;
	while (d && !(opts & LL))
	{
		if (d->name[0] == '.' && !MATCH(opts, LA))
		{
			d = d->next;
			continue ;
		}
		color_print(d, opts);
		d = d->next;
	}
	if (MATCH(opts, LL))
		lformat_handler(data, opts);
}
