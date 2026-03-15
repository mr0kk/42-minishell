/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:12:13 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/07 14:04:32 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redir(t_token_type type)
{
	return (type == FROM_FILE || type == REPLACE
		|| type == ADD_END || type == HEREDOC);
}

/*
	function checks syntax errors related to pipes
	return 1 when error happen
*/
bool	syntax_error_pipe(t_token *current)
{
	if (!current->prev && current->type == PIPE)
		return (1);
	if (current->type == PIPE && !current->next)
		return (1);
	if (current->type == PIPE && current->next && current->next->type == PIPE)
		return (1);
	if (current->token[0] == '|' && current->token[1])
		return (1);
	return (0);
}

/*
	function checks syntax errors related to redirection 
	return 1 when error happen
*/
bool	syntax_error_redir(t_token *current)
{
	if (is_redir(current->type) && !current->next)
		return (exit_syntax_error("newline"));
	if (is_redir(current->type) && current->next
		&& current->next->type == PIPE)
		return (exit_syntax_error(current->next->token));
	if (is_redir(current->type) && current->next
		&& is_redir(current->next->type))
		return (exit_syntax_error(current->next->token));
	return (0);
}

/*
	checks every syntax error
	return 1 when error occured
*/
bool	syntax_error(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (syntax_error_pipe(current))
			return (exit_syntax_error("|"));
		if (syntax_error_redir(current))
			return (1);
		current = current->next;
	}
	return (0);
}
