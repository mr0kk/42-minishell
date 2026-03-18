/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:30:00 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/17 19:30:01 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_add_replace(char **args, int i)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (!ft_strncmp(args[i], ">>", 3))
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(args[i + 1], flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(args[i + 1]);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (i + 2);
}

int	redir_from_file(char **args, int i)
{
	int	fd;

	fd = open(args[i + 1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(args[i + 1]);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (i + 2);
}
