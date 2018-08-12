/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamada <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 17:59:09 by syamada           #+#    #+#             */
/*   Updated: 2018/08/07 18:12:05 by syamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinfree_with(const char *s1, const char *s2, char c)
{
	char	*new;

	new = ft_strjoin_with(s1, s2, c);
	ft_strdel((char **)&s1);
	ft_strdel((char **)&s2);
	return (new);
}
