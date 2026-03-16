#include "minishell.h"

void	cleanup_heredocs(void)
{
	unlink(".heredoc_tmp");
}

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_signal_pid = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

int	read_heredoc(char *delimeter, int fd, char *line)
{
	int		stdin_backup;

	signal(SIGINT, heredoc_sigint_handler);
	stdin_backup = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (g_signal_pid == 130)
		{
			if (line)
				free(line);
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
			return (-1);
		}
		if (!line || ft_strncmp(line, delimeter, ft_strlen(delimeter) + 1) == 0)
		{
			if (line)
				free(line);
			break;
		}
		put_ft_util(fd, line);
	}
	close(stdin_backup);
	return (0);
}

int	process_heredoc(t_token *heredoc_node)
{
	char	*delimeter;
	char	*line;
	int		fd;

	if (!heredoc_node->next)
		return (-1);
	delimeter = heredoc_node->next->token;
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	if (read_heredoc(delimeter, fd, line) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	heredoc_node->type = FROM_FILE;
	free(heredoc_node->token);
	heredoc_node->token = ft_strdup("<");
	free(heredoc_node->next->token);
	heredoc_node->next->token = ft_strdup(".heredoc_tmp");
	return (0);
}

/*
	returns -1 if heredoc stopped by ctrl-C
*/
int	process_all_heredocs(t_token *head)
{
	t_token	*current;

	g_signal_pid = 0;
	current = head;

	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (process_heredoc(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	ignore_signals_in_parent();
	return (0);
}