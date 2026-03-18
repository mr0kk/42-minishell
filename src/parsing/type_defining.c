/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_defining.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:21:16 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/18 16:53:33 by rmrok            ###   ########.fr       */
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
