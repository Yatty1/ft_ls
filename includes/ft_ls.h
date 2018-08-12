/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:37 by syamada           #+#    #+#             */
/*   Updated: 2018/08/12 14:48:53 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <errno.h>

typedef struct	s_options
{
	int		l;
	int		r;
	int		c_r;
	int		t;
	int		a;
}				t_options;

typedef struct	s_dirs
{
	char			*path;
	struct s_dirs	*next;
}				t_dirs;

typedef struct	s_meta
{
	char	*types;
	int		n_links;
	char	*owner;
	char	*group;
	int		size;
	time_t	m_time;
	char	*name;
}				t_meta;

char			**check_option(int *argc, char **argv, t_options *opts);

#endif
