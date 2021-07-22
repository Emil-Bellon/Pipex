/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:29:44 by ebellon           #+#    #+#             */
/*   Updated: 2021/05/29 15:22:37 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_sep(const char *s, char c)
{
	size_t	i;
	size_t	nb_sep;
	char	*s_cpy;

	s_cpy = (char *)s;
	i = 0;
	nb_sep = 0;
	while (s_cpy[i])
	{
		while ((s_cpy[i] == c) && (s_cpy[i]))
			i++;
		while ((s_cpy[i] != c) && (s_cpy[i]))
			i++;
		if (s_cpy[i] == c && (s_cpy[i]))
			nb_sep++;
		if (s_cpy[i - 1] != c && (s_cpy[i] == 0))
			nb_sep++;
	}
	return (nb_sep);
}

static char	**free_tab(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs_split;
	char	*start;
	size_t	i;

	strs_split = ft_calloc(sizeof(char *), (count_sep(s, c) + 1));
	if ((count_sep(s, c) == 0))
		return (strs_split);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = (char *)s;
		while (*s && *s != c)
			s++;
		if (start != s)
		{
			strs_split[i++] = ft_strndup(start, (s - start));
			if (!strs_split)
				return (free_tab(strs_split));
		}
	}
	strs_split[i] = NULL;
	return (strs_split);
}
