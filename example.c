#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
	int	status;

	int fd = open("infile", O_RDONLY);
	if (fd < 0)
		return (printf("le fichier existe pas connard\n"));
	pid_t child = fork();
	if (child == 0)
	{
		dup2(fd, 0);
		close(fd);
		char *argv[] = {"/bin/cat", NULL};
		execve("/bin/cat", argv, envp);
		perror("execve");
	} else {
		close(fd);
		printf("coucou");
		waitpid(child, &status, 0);
	}
	return 0;
}

