/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:14 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 13:58:17 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pwd(t_token *head)
{
	char	buff[PATH];
	char	*cwd;

	cwd = getcwd(buff, PATH);
	ft_putendl_fd(cwd, STDOUT_FILENO);
}
