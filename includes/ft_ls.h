/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:38:37 by syamada           #+#    #+#             */
/*   Updated: 2018/08/18 16:59:00 by syamada          ###   ########.fr       */
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
# include <sys/xattr.h>
# include <time.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>


# define MATCH(value, flag) ((value & flag) == flag)
# define MAJOR(dev) ((int)(((unsigned int) (dev) >> 24) & 0xff))
# define MINOR(dev) ((int)((dev) & 0xff))
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
	off_t			size;
	time_t			m_time;
	char			*date;
	char			*time;
	int				major;
	int				minor;
	char			*name;
	char			*symlink;
	char			*path;
	struct s_meta	*next;
}				t_meta;

char			**check_option(int *argc, char **argv, int *opts);

/*
**
*/

void			create_data(t_meta **data, char *name, char *path);
void			delete_data(t_meta **data, int opts);
void			delete_alldata(t_meta **data, int opts);

/*
** openread
*/

void			openread_dir(char *dirname, int opts);
void			get_file(char *filename, int opts);

/*
** sorting funcs
*/

t_meta			*dispatch_sort(t_meta **data, int opts);
t_meta			*bubble_sort(t_meta **data, int is_asc);
t_meta			*time_sort(t_meta **data);
void			quick_sort(char ***input, int left, int right, int is_asc);

/*
** handlers
*/

void			lformat_handler(t_meta **data, int opts);
void			time_handler(t_meta **data, int opts);

/*
** print funcs
*/

void			print_longformat(t_meta *data, int width_size, int width_link);
void			print_dircontent(t_meta **data, int opts);

/*
** error handlers
*/
void			illegal_option(char c);
void			open_error(char *filename);

/*
** get info of files and dirs
*/

t_meta			*get_metadata(t_meta *data, int opts);
t_meta			*get_mode(struct stat st, t_meta *data);

#endif
