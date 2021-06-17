/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:23:24 by ebellon           #+#    #+#             */
/*   Updated: 2021/06/17 20:32:28 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

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

int	exec_cmd(char *cmd, char **locations, char **envp)
{
	pid_t	pid;
	char	*exec_name;
	char	*exec_path;

	exec_name = ft_strndup(cmd, ft_strnchr(cmd, ' '));
	exec_path = get_exec_path(exec_name, locations);
	if (!exec_path)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		exit(execve(exec_path, ft_split(cmd, ' '), envp));
	else 
		waitpid(pid, NULL, WNOHANG);
	return (0);
}

int exec_cmd_list(char **list, int size, char **location, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	if (size > 1)
	{
		pid = fork();
		if (pid < 0)
			return 1;
		if (pid == 0)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			exec_cmd_list(list, size - 1, location, envp);
			close(pipe_fd[1]);
			exit (0);
		}
		else
			waitpid(pid, 0, WNOHANG);
	}
	dprintf(STDERR_FILENO, "%d\n", size);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	exec_cmd(list[size - 1], location, envp);
	close(pipe_fd[0]);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	**locations;
	int		i;
	int		fd_pipe[2];

	i = ac - 1;
	locations = get_locations(envp);
	if (!locations)
		return (1);
	
	pipe(fd_pipe);
	fd_pipe[0] = open(av[1], O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
	dup2(STDIN_FILENO, fd_pipe[0]);
	// close(fd_pipe[0]);
	exec_cmd_list(av + 2, ac - 3, locations, envp);
	// dup2(open(av[ac-1], O_RDONLY | O_CREAT, 0544), STDOUT_FILENO);
	close(fd_pipe[1]);
	return (0);
}