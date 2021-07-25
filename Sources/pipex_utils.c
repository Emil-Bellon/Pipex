/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:08:46 by ebellon           #+#    #+#             */
/*   Updated: 2021/07/23 19:59:22 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strnchr(const char *const str, const char c)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**get_locations(char **envp)
{
	while (envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

char	*concat_path(char *location, char *exec)
{
	size_t	size;
	char	*out;

	size = ft_strlen(location) + ft_strlen(exec) + 1;
	out = malloc((size + 1) * sizeof(char));
	if (!out)
		return (NULL);
	while (location && *location)
		*out++ = *location++;
	*out++ = '/';
	while (exec && *exec)
		*out++ = *exec++;
	*out = '\0';
	return (out - size);
}

char	*get_exec_path(char *exec_name, char **locations)
{
	char	*buf;
	int		fd_buf;

	while (locations && *locations)
	{
		buf = concat_path(*locations, exec_name);
		fd_buf = open(buf, O_RDONLY | S_IRUSR | S_IRGRP | S_IROTH);
		if (fd_buf > 0)
		{
			close(fd_buf);
			return (buf);
		}	
		free(buf);
		locations++;
	}
	return (NULL);
}
