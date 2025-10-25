/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:47:29 by rmrok             #+#    #+#             */
/*   Updated: 2025/10/22 21:55:14 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
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

bool	is_separator(char c)
{
	return (c == ' ' || c == '\t');
}

void	skip_separators(char *input, int *index)
{
	while (input[*index] && is_separator(input[*index]))
		(*index)++;
}

char	*read_token(char *input, int *index)
{
	int		start;
	size_t	token_len;
	char	*res_token;
	char	quote_type;

	token_len = 0;
	skip_separators(input, index);
	if (!input[*index])
        return (NULL);
	start = *index;
	quote_type = 0;

	while (input[*index])
	{
		if (input[*index] == '"' || input[*index] == '\'')
		{
			if (quote_type == 0)
				quote_type = input[*index];
			else if (quote_type == input[*index])
				quote_type = 0;
		}
		if (quote_type == 0 && is_separator(input[*index]))
			break ;
		(*index)++;
	}
	token_len = *index - start;
	if (token_len == 0)
		return (NULL);

	return (ft_substr(input, start, token_len));
}

t_token *read_tokens(char *input)
{
	char	*token;
	t_token	*head;
	int		i;

	i = 0;
	head = NULL;
	while (input[i] || (i == 0 && !head))
	{
		token = read_token(input, &i);
		if (!token)
			break ;
		add_node(&head, token);
		free(token);
	}
	return (head);
}

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

void	input_handler(t_data *data)
{
	t_token *head;
	t_token	*current;
	
	head = read_tokens(data->user_input);

	current = head;
    while (current)
    {
        printf("%s\tlen: %zu\n", current->token, current->token_len);
        current = current->next;
    }

	free_tokens(&head);
}