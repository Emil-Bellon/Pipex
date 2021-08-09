/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:23:24 by ebellon           #+#    #+#             */
/*   Updated: 2021/07/30 16:22:13 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(t_pipe *const job, const int prev_in,
				char *exec_path, char **locations)
{
	if (exec_path == NULL)
		ft_free_job_exit(job->av, exec_path, locations, 1);
	if (job->flags & E_PIPEIN)
		ft_dup_close((int [2]){prev_in, STDIN_FILENO},
			job->av, exec_path, locations);
	else if (job->flags & E_FILEIN)
	{
		if (job->fd_filein < 0)
			ft_free_job_exit(job->av, exec_path, locations, 1);
		ft_dup_close((int [2]){job->fd_filein, STDIN_FILENO},
			job->av, exec_path, locations);
	}
	if (job->flags & E_PIPEOUT)
		ft_dup_close((int [2]){job->pipe_fd[1], STDOUT_FILENO},
			job->av, exec_path, locations);
	else if (job->flags & E_FILEOUT)
	{
		if (job->fd_fileout < 0)
			ft_free_job_exit(job->av, exec_path, locations, 1);
		ft_dup_close((int [2]){job->fd_fileout, STDOUT_FILENO},
			job->av, exec_path, locations);
	}
	execve(exec_path, job->av, job->envp);
	ft_putstr_fd("execve failed \n", STDERR_FILENO);
	ft_free_job_exit(job->av, exec_path, locations, 1);
}

int	ft_parent(t_pipe *const job, pid_t pid, const int prev_in)
{
	int	err;

	err = 0;
	if (job->flags & E_PIPEOUT)
		err += ft_safe_close(job->pipe_fd[1]);
	else if (job->flags & E_FILEOUT && job->fd_fileout > 0)
		err += ft_safe_close(job->fd_fileout);
	if (job->flags & E_PIPEIN)
		err += ft_safe_close(prev_in);
	else if (job->flags & E_FILEIN && job->fd_filein > 0)
		err += ft_safe_close(job->fd_filein);
	job->pid_ar[job->i++] = pid;
	return (err);
}

void	ft_exec_job(t_pipe *const job, char **locations)
{
	const int	prev_in = job->pipe_fd[0];
	pid_t		pid;
	char		*exec_path;
	int			err;

	err = 0;
	if (job->flags & E_PIPEOUT)
		pipe(job->pipe_fd);
	exec_path = get_exec_path(*job->av, locations);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork failed", STDERR_FILENO);
		ft_free_job_exit(job->av, exec_path, locations, 1);
	}
	if (pid == 0)
		ft_child(job, prev_in, exec_path, locations);
	else
		err = ft_parent(job, pid, prev_in);
	ft_free_job_exit(job->av, exec_path, locations, err);
}

int	ft_exec_pipe(size_t ac, char **av, char **envp, char **locations)
{
	t_pipe	job;
	size_t	i;
	int		ret;

	i = 2;
	job = (t_pipe){0};
	job.fd_filein = open(av[1], O_RDONLY, 0644);
	if (job.fd_filein < 0)
		printf("pipex: no such file or directory: %s\n", av[1]);
	job.fd_fileout = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (job.fd_fileout < 0)
		printf("pipex: can't create file: %s\n", av[ac - 1]);
	while (i < ac - 1)
	{
		ft_set_job(&job, i, av, ac);
		job.envp = envp;
		ft_exec_job(&job, locations);
		i++;
	}
	ret = ft_waitpids(&job);
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	char	**locations;
	int		ret;

	if (ac < 5)
	{
		printf("4 args mini : ``< infile cmd1 | cmd2 > outfile``\n");
		return (1);
	}
	locations = get_locations(envp);
	ret = ft_exec_pipe(ac, av, envp, locations);
	ft_free_tab(locations);
	return (ret);
}
