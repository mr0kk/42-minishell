/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:14 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/18 16:55:29 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(t_token *head)
{
	char	buff[PATH];
	char	*cwd;

	(void)head;
	cwd = getcwd(buff, PATH);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}
