/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:52:53 by ebellon           #+#    #+#             */
/*   Updated: 2021/05/29 15:06:48 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	char			chr;
	char			*dststr;
	char			*srcstr;

	chr = c;
	dststr = dst;
	srcstr = (char *)src;
	i = 0;
	while (i < n)
	{
		if (srcstr[i] == chr)
		{
			dststr[i] = srcstr[i];
			return (&dststr[i + 1]);
		}
		dststr[i] = srcstr[i];
		i++;
	}
	return (NULL);
}
