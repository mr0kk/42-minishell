#include "minishell.h"

void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->token)
			free(current->token);
		free(current);
		current = next;
	}
	*head = NULL;
}

t_token	*create_node(char *text)
{
	t_token *new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if(!new_node)
		exit(1);
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->token = ft_strdup(text);
	new_node->token_len = ft_strlen(text);
	new_node->type = UNKNOWN;
	return (new_node);
}

void	add_node(t_token **head, char *text)
{
	t_token	*new;
	t_token	*tmp;

	new = create_node(text);
	if (!(*head))
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}