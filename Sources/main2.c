/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:23:24 by ebellon           #+#    #+#             */
/*   Updated: 2021/07/28 20:07:16 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(t_pipe *const job, const int prev_in,
				char *name_filein, char *exec_path)
{
	if (job->flags & E_PIPEIN)
		ft_dup_close(prev_in, STDIN_FILENO);
	else if (job->flags & E_FILEIN)
	{
		if (job->fd_filein < 0)
		{
			ft_err_str("pipex: no such file or directory: ", name_filein);
			exit (1);
		}
		ft_dup_close(job->fd_filein, STDIN_FILENO);
	}
	if (job->flags & E_PIPEOUT)
		ft_dup_close(job->pipe_fd[1], STDOUT_FILENO);
	else if (job->flags & E_FILEOUT)
	{
		if (job->fd_fileout < 0)
		{
			ft_putstr_fd("pipex: can't create file\n", STDERR_FILENO);
			exit (1);
		}
		ft_dup_close(job->fd_fileout, STDOUT_FILENO);
	}
	execve(exec_path, job->av, job->envp);
	ft_putstr_fd("execve failed \n", STDERR_FILENO);
	exit (1);
}

void	ft_parent(t_pipe *const job, pid_t pid, const int prev_in)
{
	if (job->flags & E_PIPEOUT)
		ft_safe_close(job->pipe_fd[1]);
	else if (job->flags & E_FILEOUT)
		ft_safe_close(job->fd_fileout);
	if (job->flags & E_PIPEIN)
		ft_safe_close(prev_in);
	else if (job->flags & E_FILEIN && job->fd_filein > 0)
		ft_safe_close(job->fd_filein);
	job->pid_ar[job->i++] = pid;
}

void	ft_exec_job(t_pipe *const job, char **locations, char *name_filein)
{
	const int	prev_in = job->pipe_fd[0];
	pid_t		pid;
	char		*exec_path;

	if (job->flags & E_PIPEOUT)
		pipe(job->pipe_fd);
	exec_path = get_exec_path(*job->av, locations);
	if (exec_path == NULL)
	{
		ft_err_str("pipex: command not found: ", *job->av);
		ft_free_tab(job->av);
		return (free(exec_path));
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork failed", STDERR_FILENO);
		exit (1);
	}
	if (pid == 0)
		ft_child(job, prev_in, name_filein, exec_path);
	else
		ft_parent(job, pid, prev_in);
	ft_free_tab(job->av);
	free(exec_path);
}

int	ft_exec_pipe(size_t ac, char **av, char **envp, char **locations)
{
	t_pipe	job;
	size_t	i;
	int		wstatus;
	int		ret;

	i = 2;
	job = (t_pipe){0};
	while (i < ac - 1)
	{
		ft_set_job(&job, i, av, ac);
		job.envp = envp;
		ft_exec_job(&job, locations, av[1]);
		i++;
	}
	ret = ft_waitpids(&job, &wstatus);
	ft_free_tab(locations);
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	char	**locations;
	int		ret;

	if (ac < 5)
	{
		ft_putstr_fd("4 args mini : ``< infile cmd1 | cmd2 > outfile``\n", 2);
		return (1);
	}
	locations = get_locations(envp);
	ret = ft_exec_pipe(ac, av, envp, locations);
	return (ret);
}
