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

void	skip_separators(char *input, int *index)
{
	while (input[*index] && is_separator(input[*index]))
		(*index)++;
}

char	*read_token(char *input, int *index)
{
	int		start;
	char	*res_token;
	char	quote_type;

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
	if (*index - start == 0)
		return (NULL);
	return (ft_substr(input, start, *index - start));
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

void	input_handler(t_data *data)
{
	t_token *head;
	
	head = read_tokens(data->user_input);
	printf("here\n");
	define_tokens_type(head);
	printf("tu jest git\n");
	print_tokens(head);
	if (!ft_strncmp(head->token, "echo", 5))
		ft_echo(head);
	free_tokens(&head);
}