/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:23:24 by ebellon           #+#    #+#             */
/*   Updated: 2021/07/23 15:45:11 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_cmd(char *cmd, char **locations, char **envp)
{
	pid_t	pid;
	char	*exec_name;
	char	*exec_path;

	exec_name = ft_strndup(cmd, ft_strnchr(cmd, ' '));
	exec_path = get_exec_path(exec_name, locations);
	if (exec_path == NULL)
		dprintf(2, "pipex: command not found: %s\n", exec_name);
	if (!exec_path)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		exit(execve(exec_path, ft_split(cmd, ' '), envp));
	else
		waitpid(pid, NULL, WNOHANG);
	free(exec_name);
	free(exec_path);
	return (0);
}

void	ft_set_pipe(int pipe_fd[2], int size)
{
	if (size != 1)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
	}
}

int	exec_cmd_list(t_cmd_list *list, int size, char **location, char **envp)
{
	pid_t		pid;
	int			pipe_fd[2];

	pipe(pipe_fd);
	if (size > 1)
	{
		pid = fork();
		if (pid < 0)
			return (1);
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
	ft_set_pipe(pipe_fd, size);
	exec_cmd(list->list[size - 1], location, envp);
	close(pipe_fd[0]);
	return (0);
}

t_cmd_list	ft_set_cmd_list(int fd_av1, char **av, int ac)
{
	t_cmd_list	cmd_list;

	if (fd_av1 < 0)
	{
		cmd_list.list = av + 3;
		cmd_list.size = ac - 4;
	}
	else
	{
		cmd_list.list = av + 2;
		cmd_list.size = ac - 3;
	}
	return (cmd_list);
}

int	main(int ac, char **av, char **envp)
{
	char		**locations;
	int			i;
	int			io_fd[2];
	t_cmd_list	cmd_list;

	if (ac < 5)
		return (dprintf(2,
				"4 args mini : ``< infile cmd1 | cmd2 > outfile``\n"));
	i = ac - 1;
	locations = get_locations(envp);
	if (!locations)
		return (1);
	pipe(io_fd);
	io_fd[0] = open(av[1], O_RDONLY, 0644);
	if (io_fd[0] < 0)
		dprintf(2, "pipex: no such file or directory: %s\n", av[1]);
	dup2(io_fd[0], STDIN_FILENO);
	io_fd[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(io_fd[1], STDOUT_FILENO);
	cmd_list = ft_set_cmd_list(io_fd[0], av, ac);
	exec_cmd_list(&cmd_list, cmd_list.size, locations, envp);
	close(io_fd[0]);
	close(io_fd[1]);
	ft_free_tab(locations);
	return (0);
}
