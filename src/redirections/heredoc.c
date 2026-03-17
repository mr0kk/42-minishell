
#include "minishell.h"

static char	*expand_heredoc_line(char *line, t_data *data)
{
	size_t	i;
	char	*new_line;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$' && (ft_isalnum(line[i + 1])
				|| line[i + 1] == '_' || line[i + 1] == '?'))
		{
			new_line = replace_var(line, &i, data->envp, data);
			if (new_line)
			{
				free(line);
				line = new_line;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (line);
}

static int	check_and_remove_quotes(t_token *node)
{
	int		i;
	int		expand;
	char	*clean_delim;

	i = 0;
	expand = 1;
	while (node->token[i])
	{
		if (node->token[i] == '\'' || node->token[i] == '"')
			expand = 0;
		i++;
	}
	if (!expand)
	{
		clean_delim = handle_removing(node->token);
		if (clean_delim)
		{
			free(node->token);
			node->token = clean_delim;
		}
	}
	return (expand);
}

int	read_heredoc(char *delimeter, int fd, t_data *data, int expand)
{
	int		stdin_backup;
	char	*line;

	signal(SIGINT, heredoc_sigint_handler);
	stdin_backup = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (g_signal_pid == 130)
			return (abort_heredoc(stdin_backup, line));
		if (!line || ft_strncmp(line, delimeter, ft_strlen(delimeter) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
			line = expand_heredoc_line(line, data);
		put_ft_util(fd, line);
	}
	close(stdin_backup);
	return (0);
}

int	process_heredoc(t_token *heredoc_node, t_data *data)
{
	char	*delimeter;
	int		fd;
	int		expand;

	if (!heredoc_node->next)
		return (-1);
	expand = check_and_remove_quotes(heredoc_node->next);
	delimeter = heredoc_node->next->token;
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	if (read_heredoc(delimeter, fd, data, expand) == -1)
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
int	process_all_heredocs(t_token *head, t_data *data)
{
	t_token	*current;

	g_signal_pid = 0;
	current = head;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (process_heredoc(current, data) == -1)
				return (-1);
		}
		current = current->next;
	}
	ignore_signals_in_parent();
	return (0);
}
