/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:09:03 by ebellon           #+#    #+#             */
/*   Updated: 2021/07/30 16:02:27 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

typedef enum e_masks
{
	E_PIPEIN = (1 << 0),
	E_PIPEOUT = (1 << 1),
	E_FILEIN = (1 << 2),
	E_FILEOUT = (1 << 3),
}			t_masks;

typedef struct s_pipe
{
	char	flags;
	char	**av;
	char	**envp;
	int		fd_filein;
	int		fd_fileout;
	int		pipe_fd[2];
	pid_t	pid_ar[666];
	size_t	i;
}				t_pipe;

size_t	ft_strnchr(const char *const str, const char c);
void	ft_free_tab(char **tab);
char	**get_locations(char **envp);
char	*concat_path(char *location, char *exec);
char	*get_exec_path(char *exec_name, char **locations);
// void	ft_dup_close(int fd1, int fd2);
void	ft_dup_close(int fd[2], char **cmd_arg,
			char *exec_path, char **locations);
int		ft_safe_close(int fd);
void	ft_free_job_exit(char **cmd_arg, char *exec_path,
			char **locations, int err);
int		ft_waitpids(t_pipe *job);
void	ft_set_job(t_pipe *job, size_t i, char **av, size_t ac);

#endif
