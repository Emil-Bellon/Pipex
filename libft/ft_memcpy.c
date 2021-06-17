/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:58:20 by ebellon           #+#    #+#             */
/*   Updated: 2020/11/25 11:54:58 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dststr;
	unsigned char	*srcstr;

	dststr = (unsigned char *)dst;
	srcstr = (unsigned char *)src;
	if (!n || dst == src)
		return (dst);
	while (n--)
		*dststr++ = *srcstr++;
	return (dst);
}
