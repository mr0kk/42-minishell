#include "minishell.h"

/*
	function return true if chararter is structurac quote 
	returns false otherwise
*/
bool	is_structural_quote(char c, t_quote_state *state)
{
	if (*state == OUTSIDE)
	{
		if (c == '\'')
		{
			*state = IN_SINGLE;
			return (true);
		}
		else if (c == '\"')
		{
			*state = IN_DOUBLE;
			return (true);
		}
	}
	else if (*state == IN_SINGLE && c == '\'')
	{
		*state = OUTSIDE;
		return (true);
	}
	else if (*state == IN_DOUBLE && c == '\"')
	{
		*state = OUTSIDE;
		return (true);
	}
	return (false);
}

/*
	for given token string function iterates throuht it 
	and copy every character to new string if it's not 
	a structurac quote
*/
char	*handle_removing(char *old_token)
{
	size_t	i;
	size_t	j;
	t_quote_state state;
	char	*new_token;

	i = 0;
	j = 0;
	state = OUTSIDE;
	new_token = (char *)malloc((ft_strlen(old_token) + 1) * sizeof(char));
	if (!new_token)
		return (NULL);
	while (old_token[i])
	{
		if (is_structural_quote(old_token[i], &state))
			i++;
		else
		{
			new_token[j] = old_token[i];
			i++;
			j++;
		}
	}
	new_token[j] = '\0';
	return (new_token);
}

/*
	function iterates throught each token and calls function
	that handle whole removing process for every CMD,
	ARG or FILE_TOKEN token types
*/
void	remove_quotes(t_token *head)
{
	t_token *current;
	char	*clear_token;

	current = head;
	while (current)
	{
		if (current->type == CMD || current->type == ARG || current->type == FILE_TOKEN)
		{
			clear_token = handle_removing(current->token);
			if (clear_token)
			{
				free(current->token);
				current->token = clear_token;
			}
		}
		current = current->next;
	}
}