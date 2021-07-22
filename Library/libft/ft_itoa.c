/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:38:36 by ebellon           #+#    #+#             */
/*   Updated: 2021/05/29 15:05:38 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static size_t	ft_count_digit(int n)
{
	long	nbr;
	size_t	nb_digit;

	nbr = n;
	nb_digit = 0;
	if (nbr < 0)
	{
		nb_digit++;
		nbr = -nbr;
	}
	while (nbr >= 10)
	{
		nbr /= 10;
		nb_digit++;
	}
	nb_digit++;
	return (nb_digit);
}

char	*ft_itoa(int n)
{
	long	nb;
	size_t	nb_digit;
	char	*nbr;

	nb = n;
	nb_digit = ft_count_digit(n);
	nbr = ft_calloc(nb_digit + 1, sizeof(char));
	if (nbr == NULL)
		return (NULL);
	nb_digit--;
	if (nb < 0)
	{
		*nbr = '-';
		nb = -nb;
	}
	while (nb >= 10)
	{
		nbr[nb_digit] = (nb % 10) + 48;
		nb /= 10;
		nb_digit--;
	}
	nbr[nb_digit] = (nb % 10) + 48;
	return (nbr);
}
