/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:12:13 by rmrok             #+#    #+#             */
/*   Updated: 2025/10/29 20:34:52 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if ((current->type == REDIR_IN || current->type == REDIR_OUT) && !current->next) // > at end
		return (exit_syntax_error(current->token));
	if ((current->type == REDIR_IN || current->type == REDIR_OUT) && current->next && current->next->type == PIPE)
		return (exit_syntax_error(current->token));
	if ((current->type == REDIR_IN || current->type == REDIR_OUT) && current->next && // > < or < >
		(current->next->type == REDIR_IN || current->next->type == REDIR_OUT))
		return (exit_syntax_error(current->token));
	return (0);
}

/*
	checks every syntax error
	return 1 when error occured
*/
bool	syntax_error(t_token *head)
{
	t_token *current;
	
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