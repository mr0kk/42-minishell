/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:51:29 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/17 15:21:34 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_from_file(char **args, int i)
{
	int	fd;

	fd = open(args[i + 1], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (i + 2);
}
