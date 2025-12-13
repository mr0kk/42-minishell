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

/*
	function update quotes status 
	depending if any quote is open or not
*/
void	update_quote_state(char c, t_quote_state *state)
{
	if (*state == OUTSIDE)
	{
		if (c == '\'')
			*state = IN_SINGLE;
		else if (c == '\"')
			*state = IN_DOUBLE;
	}
	else if (*state == IN_SINGLE)
	{
		if (c == '\'')
            *state = OUTSIDE;
	}
	else if (*state == IN_DOUBLE)
	{
		if (c == '\"')
			*state = OUTSIDE;
	}
}
