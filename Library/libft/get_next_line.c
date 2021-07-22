/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:40:05 by pthomas           #+#    #+#             */
/*   Updated: 2021/06/17 13:35:49 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(const char *s1, const char *s2)
{
	int		i;
	char	*line;

	i = -1;
	line = ft_calloc((ft_strlen(s1) + 2), sizeof(char));
	if (line == NULL)
		return (0);
	while (s1[++i])
		line[i] = s1[i];
	line[i++] = s2[0];
	line[i] = '\0';
	free((char *)s1);
	return (line);
}

int	get_next_line(int fd, char **line)
{
	char	buf[2];
	int		ret;

	if (!line)
		return (-1);
	(*line) = ft_calloc(1, sizeof(char));
	if (!(*line))
		return (-1);
	**line = 0;
	ret = 0;
	while (1)
	{
		ret = read(fd, buf, 1);
		if (ret == -1)
			return (-1);
		if (*buf == '\n' || ret == 0)
			break ;
		(*line) = ft_strjoin_gnl(*line, buf);
		if (!(*line))
			return (-1);
	}
	return (ret);
}
