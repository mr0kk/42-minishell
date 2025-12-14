#include "minishell.h"

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
    {
        printf("%s\ttype: %d\n", current->token, current->type);
        current = current->next;
    }
}

void	check_for_pipe(t_token *head, char **envp)
{
	t_token *current;
	char	*commands[2];

	current = head;
	commands[0] = current->token;
	while (current)
	{
		if(current->type == PIPE)
		{
			commands[1] = current->next->token;
			pipes(commands, envp);
		}
		current = current->next;
	}
}

bool	is_separator(char c)
{
	return (c == ' ' || c == '\t');
}

/*
	helper function for freeing stings
*/
char	*free_vars(char	*a, char *b, char *c)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	return (NULL);
}

void	check_for_buildins(t_token *head, t_data *data, int *fd, int i)
{
	if (ft_strncmp(head->token, "cd", 3) == 0)
		cmd_cd(head);
	else if (ft_strncmp(head->token, "echo", 5) == 0)
		cmd_echo(head);
	else if (ft_strncmp(head->token, "env", 4) == 0)
		cmd_env(data);
	else if (ft_strncmp(head->token, "export", 7) == 0)
		cmd_export(head, data);
	else if (ft_strncmp(head->token, "pwd", 4) == 0)
		cmd_pwd(head);
	else if (ft_strncmp(head->token, "unset", 6) == 0)
		cmd_unset(head, data);
	else if (ft_strncmp(head->token, "exit", 5) == 0)
		cmd_exit(head);
	else
		exec_cmd(head->token, data->envp, fd, i);
}