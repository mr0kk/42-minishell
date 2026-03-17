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

int	cmd_echo(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return (1);
	tmp = head->next;
	if (!tmp)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	if (!ft_strncmp(tmp->token, "-n", 3))
	{
		if (tmp->next)
			ft_putstr_fd(tmp->next->token, STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(tmp->token, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}
