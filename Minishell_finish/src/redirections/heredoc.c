#include "minishell.h"

#define MAX_LINE 1024

// np cat << EOF - wprowadza blok tekstu jako wejście programu

void	redir_heredoc(t_token *head, t_data *data)
{
	int pipes[2];
	int pid;
	char **parts;
	char buffer[MAX_LINE];
	ssize_t len;

	parts = get_redir_parts(head);
	if (pipe(pipes) == -1)
	{
		printf("error pipe");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		printf("error fork");
		exit(1);
	}
	if (pid == 0)
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		exec_cmd_redir(parts[0], data->envp);
	}
	else
	{
		close(pipes[0]);
		while (1)
		{
			write(STDOUT_FILENO, "heredoc> ", 9);
			len = read_line(buffer, MAX_LINE);
			if (len <= 0)
				break;
			buffer[len] = '\0';
			if(ft_strcmp(buffer, parts[1]) == 0);
				break;
			write(pipes[1], buffer, len);
			write(pipes[1], "\n", 1);
		}
		close(pipes[1]);
		waitpid(pid, NULL, 0);
	}
}
