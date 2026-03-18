/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:49:59 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/18 16:55:55 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_flag(const char *str)
{
	size_t	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	cmd_echo(t_token *head)
{
	t_token	*current;
	bool	print_newline;

	print_newline = true;
	current = head->next;
	while (current && current->type == ARG && is_n_flag(current->token))
	{
		print_newline = false;
		current = current->next;
	}
	while (current && current->type == ARG)
	{
		ft_putstr_fd(current->token, STDOUT_FILENO);
		if (current->next && current->next->type == ARG)
			ft_putchar_fd(' ', STDOUT_FILENO);
		current = current->next;
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
