/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:23:24 by ebellon           #+#    #+#             */
/*   Updated: 2021/07/25 05:21:43 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TO DO : verif syscall

void	ft_exec_job(t_pipe *const job, char **locations, char *name_filein)
{
	const int	prev_in = job->pipe_fd[0];
	pid_t	pid;
	char	*exec_path;
	
	if (job->flags & E_PIPEOUT)
		pipe(job->pipe_fd);
	exec_path = get_exec_path(*job->av, locations);
	if (exec_path == NULL)
	{
		dprintf(2, "pipex: command not found: %s\n", *job->av);
		return ;
	}
	pid = fork();
	if (pid < 0)
		exit (1);
	if (pid == 0)
	{
		if (job->flags & E_PIPEIN)
		{
			dup2(prev_in, STDIN_FILENO);
			// close(prev_in);
		}
		else if (job->flags & E_FILEIN)
		{
			dup2(job->fd_filein, STDIN_FILENO);
			// close(job->fd_filein);
			if (job->fd_filein < 0)
			{
				dprintf(2, "pipex: no such file or directory: %s\n", name_filein);
				exit (1);
			}
		}
		if (job->flags & E_PIPEOUT)
		{
			dup2(job->pipe_fd[1], STDOUT_FILENO);
			close(job->pipe_fd[0]);
		}
		else if (job->flags & E_FILEOUT)
		{
			dup2(job->fd_fileout, STDOUT_FILENO);
			// close(job->fd_fileout);
		}
		dprintf(2, "execve failed : %d\n", execve(exec_path, job->av, job->envp));
		exit (1);
	}
	else
	{
		if (job->flags & E_PIPEOUT)
			close(job->pipe_fd[1]);
		else if (job->flags & E_FILEOUT)
			close(job->fd_fileout);
		if (job->flags & E_PIPEIN)
			close(prev_in);
		else if (job->flags & E_FILEIN)
			close(job->fd_filein);
		job->pid_ar[job->i++] = pid;
	}
	ft_free_tab(job->av);
	free(exec_path);
}

int	ft_waitpids(t_pipe *job, int *wstatus)
{
	size_t	i;
	int		ret;
	
	i = 0;
	while (i < job->i)
	{
		waitpid(job->pid_ar[i++], wstatus, 0);
		if (WIFEXITED(*wstatus))
			ret = WEXITSTATUS(*wstatus);
	}
	return (ret);
}

// void	ft_set_job

int	ft_exec_pipe(size_t ac, char **av, char **envp, char **locations)
{
	t_pipe	job = {0};
	size_t	i;
	int		wstatus;
	int		ret;
	
	i = 2;
	while (i < ac - 1)
	{
		if (i == 2)
		{
			job.flags |= (E_FILEIN | E_PIPEOUT);
			job.flags &= ~(E_PIPEIN | E_FILEOUT);
			job.fd_filein = open(av[1], O_RDONLY, 0644);
		}
		else if (i == ac - 2)
		{
			job.flags |= (E_PIPEIN | E_FILEOUT);
			job.flags &= ~(E_FILEIN | E_PIPEOUT);
			job.fd_fileout = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		if (i != 2 && i != ac - 2)
		{
			job.flags |= (E_PIPEIN | E_PIPEOUT);
			job.flags &= ~(E_FILEIN | E_FILEOUT);
		}
		job.envp = envp;
		job.av = ft_split(av[i], ' ');
		ft_exec_job(&job, locations, av[1]);
		i++;
	}
	ret = ft_waitpids(&job, &wstatus);
	ft_free_tab(locations);
	return ((unsigned char)ret);
}

int	main(int ac, char **av, char **envp)
{
	char **locations;
	int ret;
	if (ac < 5)
	{
		dprintf(2, "4 args mini : ``< infile cmd1 | cmd2 > outfile``\n");
		return (1);
	}
	locations = get_locations(envp);
	ret = ft_exec_pipe(ac, av, envp, locations);
	return (ret);
}