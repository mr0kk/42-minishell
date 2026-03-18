/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:51:08 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/17 16:57:02 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_operator_token(char *input, int *index)
{
	int		start;

	start = *index;
	(*index)++;
	if ((input[start] == '<' && input[*index] == '<')
		|| (input[start] == '>' && input[*index] == '>'))
		(*index)++;
	return (ft_substr(input, start, *index - start));
}

static char	*read_word_token(char *input, int *index)
{
	int		start;
	char	quote_type;

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
		if (quote_type == 0 && (is_separator(input[*index])
				|| ft_strchr("<>|", input[*index])))
			break ;
		(*index)++;
	}
	if (*index - start == 0)
		return (NULL);
	return (ft_substr(input, start, *index - start));
}

char	*read_token(char *input, int *index)
{
	skip_separators(input, index);
	if (!input[*index])
		return (NULL);
	if (ft_strchr("<>|", input[*index]))
		return (read_operator_token(input, index));
	return (read_word_token(input, index));
}

/*
	function takes input string and separetes it 
	creating tokens
	returns head element of linked list
*/
t_token	*read_tokens(char *input)
{
	char	*token;
	t_token	*head;
	int		i;

	i = 0;
	head = NULL;
	while (1)
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
	t_token	*head;

	head = read_tokens(data->user_input);
	if (!head)
		return ;
	data->head = head;
	define_tokens_type(head);
	if (syntax_error(head) || expand_variables(head, data->envp, data))
	{
		data->last_exit_code = 2;
		free_tokens(&(data->head));
		data->head = NULL;
		return ;
	}
	if (process_all_heredocs(data->head, data) == -1)
	{
		data->last_exit_code = 130;
		free_tokens(&(data->head));
		data->head = NULL;
		return ;
	}
	start_execution(data->head, data);
	unlink(".heredoc_tmp");
	free_tokens(&(data->head));
}
