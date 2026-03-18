/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:51:29 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/18 16:53:13 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (i + 2);
}
