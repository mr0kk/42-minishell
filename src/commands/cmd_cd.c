/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:49:52 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 13:59:26 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_cd(t_token *head)
{
	t_token	*tmp;
	char	*path;

	if (!head)
		return ;
	tmp = head->next;
	if (!tmp)
		return ;
	chdir(tmp->token);
}
