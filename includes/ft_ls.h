/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:37 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 16:21:00 by syamada          ###   ########.fr       */
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
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

# define MATCH(value, flag) ((value & flag) == flag)

typedef struct	s_options
{
	int		l;
	int		r;
	int		c_r;
	int		t;
	int		a;
}				t_options;

typedef struct	s_meta
{
	char			*mode;
	unsigned int	n_links;
	char			*owner;
	char			*group;
	int				size;
	time_t			m_time;
	char			*name;
	char			*symlink;
	char			*path;
}				t_meta;

char			**check_option(int *argc, char **argv, t_options *opts);

/*
** sorting funcs
*/

void			quick_sort(char ***input, int left, int right, int is_asc);
char			**sort_content(t_list *list, int is_asc);

/*
** error handlers
*/

void			illegal_option(char c);

/*
** get info of files and dirs
*/
t_meta			*get_metadata(struct stat st, t_meta *data, t_options opts);
t_meta			*get_mode(struct stat st, t_meta *data);
char			get_filetype(struct stat st);
char			get_execpermit(struct stat st);

#endif
