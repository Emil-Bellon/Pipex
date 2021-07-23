/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:09:03 by ebellon           #+#    #+#             */
/*   Updated: 2021/07/23 14:12:23 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_cmd_list
{
	char	**list;
	size_t	size;
}				t_cmd_list;

size_t	ft_strnchr(const char *const str, const char c);
void	ft_free_tab(char **tab);
char	**get_locations(char **envp);
char	*concat_path(char *location, char *exec);
char	*get_exec_path(char *exec_name, char **locations);

#endif
