/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:49:59 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/17 16:55:57 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_printer(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
}

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
		while (tmp && tmp->type == ARG)
		{
			echo_printer(tmp->token);
			tmp = tmp->next;
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}
