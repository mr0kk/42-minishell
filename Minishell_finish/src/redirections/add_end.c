#include "minishell.h"

// np ls >> plik - dopisuje na koniec pliku wynikiem komendy

void	redir_add_end(t_token *head, t_data *data)
{
	int pid;
	int fd;
	char **parts;

	parts = get_redir_parts(head);
	pid = fork();
	if (pid < 0)
	{
		printf("error fork");
		exit(1);
	}
	if (pid == 0)
	{
		fd = open(parts[1], O_WRONLY | O_CREAT | O_APPEND);
		if (fd < 0)
		{
			printf("error open");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		exec_cmd_redir(parts[0], data->envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}
