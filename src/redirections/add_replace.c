/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:51:25 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/17 15:21:30 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_add_replace(char **args, int i)
{
	int	fd;

	if (!ft_strncmp(args[i], ">>", 3))
		fd = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (i + 2);
}
