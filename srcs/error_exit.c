/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:29:35 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 15:16:32 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	illegal_option(char c)
{
	ft_putstr_fd("./ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage: ./ft_ls [-arRltG] [file...]", 2);
	exit(-1);
}

void	open_error(char *filename)
{
	char	*str;

	ft_putstr_fd("./ft_ls: ", 2);
	if (errno == EACCES)
	{
		str = ft_strlast(filename, '/');
		ft_putstr_fd(str, 2);
		free(str);
	}
	else
		ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}
