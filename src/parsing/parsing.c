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

void	add_env(t_data *data, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp && envp[i] != NULL)
		i++;
	if (getenv("USER") == NULL)
		i++;
	data->envp = ft_calloc(i + 1, sizeof * data->envp);
	if (!data->envp)
		exit_shell("Memory allocation error");
	j = 0;
	while (envp && envp[j])
	{
		data->envp[j] = ft_strdup(envp[j]);
		if (!data->envp[j])
			exit_shell("Memory allocation error");
		j++;
	}
	if (getenv("USER") == NULL)
		data->envp[j] = ft_strdup("USER=guest");
}

/*
	function iterates throught separators to skip them
*/
void	skip_separators(char *input, int *index)
{
	while (input[*index] && is_separator(input[*index]))
		(*index)++;
}

/*
	function separates first met token from given string
	and updates index variable for next index after token
	return token string
*/
char	*read_token(char *input, int *index)
{
	int		start;
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
	// "echo test"
	// remove_quotes(head);
	// echo test
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
