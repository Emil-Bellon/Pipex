/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:33:15 by ebellon           #+#    #+#             */
/*   Updated: 2021/05/29 15:32:26 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char const c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*end;
	char		*str;

	if (!s1)
		return (NULL);
	end = s1 + ft_strlen(s1) - 1;
	while (ft_isinset(*s1, set))
		s1++;
	if (!*s1)
	{
		str = ft_calloc(1, sizeof(char));
		if (str == NULL)
			return (NULL);
		return (str);
	}
	while (ft_isinset(*end, set))
		end--;
	str = ft_calloc(end - s1 + 2, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, end - s1 + 2);
	return (str);
}
