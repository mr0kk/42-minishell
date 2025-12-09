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
	if there is $ sign in token
	return $ index 
	or NULL when not
*/
int	is_dolar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 36 && ft_isalpha(s[i + 1]) )  // 36 -> dolar sign
			return (i);
		i++;
	}
	return (-1);
}