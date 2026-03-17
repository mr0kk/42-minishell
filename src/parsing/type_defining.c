/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_defining.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:21:16 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/17 15:21:18 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	classify_token(t_token *token)
{
	if (!ft_strncmp(token->token, "|", 2))
		token->type = PIPE;
	else if (!ft_strncmp(token->token, "<", 2))
		token->type = FROM_FILE;
	else if (!ft_strncmp(token->token, ">", 2))
		token->type = REPLACE;
	else if (!ft_strncmp(token->token, ">>", 3))
		token->type = ADD_END;
	else if (!ft_strncmp(token->token, "<<", 3))
		token->type = HEREDOC;
	else if (token->prev == NULL || token->prev->type == PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}

/*
	function assigns each token in the linked list 
	token type
*/
void	define_tokens_type(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		classify_token(tmp);
		tmp = tmp->next;
	}
}
