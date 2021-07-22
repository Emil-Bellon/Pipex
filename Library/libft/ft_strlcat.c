/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 08:01:30 by ebellon           #+#    #+#             */
/*   Updated: 2020/12/10 14:09:01 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ldst;
	size_t	lsrc;

	i = 0;
	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (ldst >= dstsize)
		return (dstsize + lsrc);
	while (src[i] && (i + ldst < dstsize - 1))
	{
		dst[ldst + i] = src[i];
		i++;
	}
	dst[ldst + i] = 0;
	return (ldst + lsrc);
}
