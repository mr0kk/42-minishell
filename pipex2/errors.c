/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:57:51 by ajurczyk          #+#    #+#             */
/*   Updated: 2025/05/10 16:32:51 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wrong_file_av1(char *s)
{
	if (access(s, F_OK) == 0)
	{
		ft_putstr_fd("pipex: permission denied: ", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("pipex: no such file or directory :", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void	wrong_file_av2(char *s)
{
	if (access(s, F_OK) == 0)
	{
		ft_putstr_fd("pipex: permission denied: ", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void	wrong_command(char *s)
{
	ft_putstr_fd("pipex: command not found :", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
