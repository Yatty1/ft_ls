/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 15:14:40 by syamada           #+#    #+#             */
/*   Updated: 2018/08/20 15:19:08 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		get_attributes(struct stat st, char path[PATH_MAX])
{
	char	buf[100];
	acl_t	tmp;

	if (listxattr(path, buf, 100, XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_link_np(path, ACL_TYPE_EXTENDED)) > 0)
	{
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}
