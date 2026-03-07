#include "minishell.h"

char	**get_redir_parts(t_token *head)
{
	t_token *curr;
	char **parts;
	char *tmp;

	curr = head;
	parts = (char **)calloc(2, sizeof(char *));
	if (curr->type != FROM_FILE || curr->type != REPLACE || curr->type != ADD_END || curr->type != HEREDOC)
	{
		tmp = parts[0];
		parts[0] = ft_strjoin(tmp, curr->token);
		tmp = parts[0];
		parts[0] = ft_strjoin(tmp, " ");
		curr = curr->next;
	}
	curr = curr->next;
	tmp = parts[1];
	parts[1] = ft_strjoin(tmp, curr->token);
	tmp = parts[1];
	parts[1] = ft_strjoin(tmp, " ");
	return(parts);
}

void exec_cmd_redir(char *cmd, char **envp)
{
	char	*arg0;
	char	*tmp;
	char	**args;
	// int		pid;

	// pid = fork();
	// if (pid == 0)
	// {
		args = ft_split(cmd, ' ');
		if (check_command(envp, args[0]))
		{
			printf("wrong command %s\n", args[0]);
			free(args);
			exit(1);
		}
		arg0 = get_path(envp, args[0]);
		if (execve(arg0, args, envp) == -1)
		{
			printf("blad execve\n");
			free(arg0);
			free(args);
			exit(1);
		}
	// }
	// waitpid(pid, NULL, 0);
}

ssize_t read_line(char *buffer, size_t size) 
{
    size_t i = 0;
    char c;

    while (i < size - 1) {
        ssize_t r = read(STDIN_FILENO, &c, 1);
        if (r <= 0)
            return r;

        if (c == '\n')
            break;

        buffer[i++] = c;
    }

    buffer[i] = '\0';
    return i;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
