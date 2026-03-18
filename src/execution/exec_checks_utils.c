/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:54:35 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/18 16:54:36 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_and_close(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

int	replace_add_setup(t_token *curr, int *fd)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (curr->type == REPLACE)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	*fd = open(curr->next->token, flags, 0644);
	if (*fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(curr->next->token);
		return (1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
		return (perror("minishell: dup2"), 1);
	close(*fd);
	return (0);
}
