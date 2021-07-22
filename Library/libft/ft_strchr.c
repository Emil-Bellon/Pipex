/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 07:37:05 by ebellon           #+#    #+#             */
/*   Updated: 2020/11/25 14:30:31 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	chr;

	str = (unsigned char *)s;
	chr = (unsigned char)c;
	while (*str != chr)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *)str);
}
