/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 10:33:19 by syamada           #+#    #+#             */
/*   Updated: 2018/08/19 17:05:01 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_meta			*dispatch_sort(t_meta **data, int opts)
{
	if (MATCH(opts, LT))
		return (time_sort(data));
	return (bubble_sort(data, !MATCH(opts, LR)));
}
