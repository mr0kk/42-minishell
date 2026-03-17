
#include "minishell.h"

bool	is_separator(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_builtin(t_token *token)
{
	if (!token || token->type != CMD)
		return (false);
	if (ft_strncmp(token->token, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(token->token, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(token->token, "env", 4) == 0)
		return (true);
	if (ft_strncmp(token->token, "export", 7) == 0)
		return (true);
	if (ft_strncmp(token->token, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(token->token, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(token->token, "exit", 5) == 0)
		return (true);
	return (false);
}

/*
	this function returns number of pipes
	in the user input
*/
int	check_for_pipes(t_token *head)
{
	t_token	*current;
	int		numofpipes;

	current = head;
	numofpipes = 0;
	while (current)
	{
		if (current->type == PIPE)
			numofpipes++;
		current = current->next;
	}
	return (numofpipes);
}
