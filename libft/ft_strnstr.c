/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:27:28 by ebellon           #+#    #+#             */
/*   Updated: 2021/05/30 14:10:55 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hstck, const char *ndl, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lndle;

	if (ndl[0] == 0)
		return ((char *)hstck);
	i = 0;
	lndle = ft_strlen(ndl);
	while (i < len && hstck[i])
	{
		j = 0;
		while (hstck[i + j] && ndl[j] && hstck[i + j] == ndl[j] && i + j < len)
			j++;
		if (!ndl[j])
			return ((char *)&hstck[i]);
		i++;
	}
	return (NULL);
}
