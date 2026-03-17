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

int	cmd_cd(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return (1);
	tmp = head->next;
	if (!tmp)
		return (0);
	if (chdir(tmp->token) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
