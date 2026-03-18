/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:04 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/18 16:55:52 by rmrok            ###   ########.fr       */
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
