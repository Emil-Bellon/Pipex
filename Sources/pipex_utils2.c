/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:43:10 by ebellon           #+#    #+#             */
/*   Updated: 2021/07/28 19:46:37 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) < 0)
	{
		ft_putstr_fd("dup2 failed\n", STDERR_FILENO);
		exit(1);
	}
	if (close(fd1) < 0)
	{
		ft_putstr_fd("close failed\n", STDERR_FILENO);
		exit(1);
	}
}

void	ft_safe_close(int fd)
{
	if (close(fd) < 0)
	{
		ft_putstr_fd("close failed\n", STDERR_FILENO);
		exit(1);
	}
}

void	ft_err_str(char *str, char *arg)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
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

void	ft_set_job(t_pipe *job, size_t i, char **av, size_t ac)
{
	if (i == 2)
	{
		job->flags |= (E_FILEIN | E_PIPEOUT);
		job->flags &= ~(E_PIPEIN | E_FILEOUT);
		job->fd_filein = open(av[1], O_RDONLY, 0644);
	}
	else if (i == ac - 2)
	{
		job->flags |= (E_PIPEIN | E_FILEOUT);
		job->flags &= ~(E_FILEIN | E_PIPEOUT);
		job->fd_fileout = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	if (i != 2 && i != ac - 2)
	{
		job->flags |= (E_PIPEIN | E_PIPEOUT);
		job->flags &= ~(E_FILEIN | E_FILEOUT);
	}
	job->av = ft_split(av[i], ' ');
}
