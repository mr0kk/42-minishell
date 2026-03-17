/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:04 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 13:58:39 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
		ft_putendl_fd(data->envp[i++], STDOUT_FILENO);
	return (0);
}
