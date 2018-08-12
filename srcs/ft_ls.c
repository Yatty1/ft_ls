/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:26 by syamada           #+#    #+#             */
/*   Updated: 2018/08/11 21:48:06 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*dp;

	if (argc == 1)
		return (0);
	if (!(dir = opendir(argv[1])))
		return (0);
	while ((dp = readdir(dir)))
	{
		ft_printf("file num:%s\n", dp->d_name);
	}
	closedir(dir);
	return (0);
}
