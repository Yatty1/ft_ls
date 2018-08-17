/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:37 by syamada           #+#    #+#             */
/*   Updated: 2018/08/16 23:20:03 by syamada          ###   ########.fr       */
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
# define HALF_A_YEAR 15778463
# define LL 1
# define LR 2
# define CR 4
# define LT 8
# define LA 16

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
	struct s_meta	*next;
}				t_meta;

char			**check_option(int *argc, char **argv, int *opts);

void			create_data(t_meta **data, char *name, char *path);

/*
** sorting funcs
*/

t_meta			*bubble_sort(t_meta **data, int is_asc);
void			quick_sort(char ***input, int left, int right, int is_asc);
char			**sort_content(t_list *list, int is_asc);

/*
** print funcs
*/

void			print_longformat(t_meta *data);
void			print_dircontent(t_meta *data);

/*
** error handlers
*/

void			illegal_option(char c);

/*
** get info of files and dirs
*/

t_meta			*get_metadata(struct stat st, t_meta *data, int opts);
t_meta			*get_mode(struct stat st, t_meta *data);
char			get_filetype(struct stat st);
char			get_execpermit(struct stat st);

#endif
