#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../headers/minishell.h"

int	main(void)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe fail\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork fail\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		false_exec(cmd 1,args,  sort1, ent1);
		close(fd[1]);
	}
	else
	{
		char	*line;
		line = NULL;
		close(fd[1]);
		dup2(fd[0], 0);
		line = get_next_line(fd[0]);
		if (!line)
			exit(write(1, "error\n", 6));
		printf("%s", line);
	}
	close(fd[0]);
	wait(NULL);
}