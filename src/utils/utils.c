#include "minishell.h"

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
    {
        printf("%s\n", current->token);
        current = current->next;
    }
}

bool	is_separator(char c)
{
	return (c == ' ' || c == '\t');
}