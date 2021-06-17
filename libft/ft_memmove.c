/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:22:02 by ebellon           #+#    #+#             */
/*   Updated: 2020/11/25 12:12:48 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dststr;
	unsigned char	*srcstr;

	if (!dst && !src)
		return (NULL);
	i = 0;
	dststr = (unsigned char *)dst;
	srcstr = (unsigned char *)src;
	while (i < len)
	{
		if (dst > src)
			dststr[len - i - 1] = srcstr[len - i - 1];
		else
			dststr[i] = srcstr[i];
		i++;
	}
	return (dst);
}
