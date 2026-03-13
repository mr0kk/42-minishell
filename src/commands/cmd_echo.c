/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:49:59 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 13:58:52 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	tmp = head->next;
	if (!ft_strncmp(tmp->token, "-n", 3))
		ft_putstr_fd(tmp->next->token, STDOUT_FILENO);
	else
	{
		ft_putstr_fd(tmp->token, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
