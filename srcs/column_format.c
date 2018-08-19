/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colum_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 11:19:58 by syamada           #+#    #+#             */
/*   Updated: 2018/08/19 14:58:00 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** displays exactly as LIBC LS, from top to bottom and left to right instead of
** left to right and then top to bottom.
*/

static int	lst_column(t_file *lst, t_index row_col, t_index maxlen, int flags)
{
	int				tmp_column;
	int				tmp_row;
	t_file			*lst_tmp;
	int				counter;

	counter = row_col.y;
	while (lst && counter--)
	{
		tmp_column = row_col.x;
		lst_tmp = lst->next;
		while (lst && tmp_column--)
		{
			display_name(lst, flags, maxlen.y);
			if (tmp_column)
				ft_putnchar(MAX(maxlen.x - ft_strlen(lst->name), 0), ' ');
			tmp_row = row_col.y;
			while (lst && tmp_row--)
				lst = lst->next;
		}
		ft_putchar('\n');
		lst = lst_tmp;
	}
	return (1);
}

/*
** bonus on columns
** padding is done according to the longest file name (maxlen.x)
** maxlen.y is used for -s option to calculate the width of blocks display
** so we need to go through the list once in order to get maxlen (tmp).
** if (!(flags & 128) checks for -1 option, row will be number of element.
*/

static int	display_basic_list(t_file *lst, int flags)
{
	t_index			maxlen;
	struct ttysize	ts;
	t_index			i;
	t_file			*tmp_lst;
	int				total;

	total = 0;
	maxlen.x = lst_maxlen(lst) + ((flags & LS_G) ? 1 : 4);
	maxlen.y = (flags & LS_S) ? lst_blocks_len(lst, &total) : 0;
	if (flags & LS_S)
		ft_printf("total %d\n", total);
	ioctl(0, TIOCGWINSZ, &ts);
	i.x = (!(flags & 128)) ? ts.ts_cols / (maxlen.x + maxlen.y) : 1;
	i.y = 0;
	tmp_lst = lst;
	while (tmp_lst)
	{
		++i.y;
		tmp_lst = tmp_lst->next;
	}
	if (!(flags & 128))
		i.y = (i.y % i.x ? 1 : 0) + (i.y / i.x);
	lst_column(lst, i, maxlen, flags);
	return (1);
}
