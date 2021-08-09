/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:43:10 by ebellon           #+#    #+#             */
/*   Updated: 2021/08/09 12:02:02 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup_close(int fd[2], char **cmd_arg,
					char *exec_path, char **locations)
{
	if (dup2(fd[0], fd[1]) < 0)
	{
		ft_putstr_fd("dup2 failed\n", STDERR_FILENO);
		ft_free_job_exit(cmd_arg, exec_path, locations, 1);
	}
	if (close(fd[0]) < 0)
	{
		ft_putstr_fd("close failed\n", STDERR_FILENO);
		ft_free_job_exit(cmd_arg, exec_path, locations, 1);
	}
}

int	ft_safe_close(int fd)
{
	if (close(fd) < 0)
	{
		ft_putstr_fd("close failed\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void	ft_free_job_exit(char **cmd_arg, char *exec_path,
						char **locations, int err)
{
	ft_free_tab(cmd_arg);
	free(exec_path);
	if (err > 0)
	{
		ft_free_tab(locations);
		exit (1);
	}
}

int	ft_waitpids(t_pipe *job)
{
	size_t	i;
	int		ret;
	int		wstatus;

	i = 0;
	while (i < job->i)
	{
		waitpid(job->pid_ar[i++], &wstatus, 0);
		if (WIFEXITED(wstatus))
			ret = WEXITSTATUS(wstatus);
	}
	return (ret);
}

void	ft_set_job(t_pipe *job, size_t i, char **av, size_t ac)
{
	if (i == 2)
	{
		job->flags |= (E_FILEIN | E_PIPEOUT);
		job->flags &= ~(E_PIPEIN | E_FILEOUT);
	}
	else if (i == ac - 2)
	{
		job->flags |= (E_PIPEIN | E_FILEOUT);
		job->flags &= ~(E_FILEIN | E_PIPEOUT);
	}
	if (i != 2 && i != ac - 2)
	{
		job->flags |= (E_PIPEIN | E_PIPEOUT);
		job->flags &= ~(E_FILEIN | E_FILEOUT);
	}
	job->av = ft_split(av[i], ' ');
}
