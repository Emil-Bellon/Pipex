/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:05:57 by ebellon           #+#    #+#             */
/*   Updated: 2021/05/29 15:07:14 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char	*tmp;

	tmp = b;
	while (len > 0)
	{
		*tmp = c;
		tmp++;
		len--;
	}
	return (b);
}
