/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:18 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 13:59:05 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_data *data, int idx)
{
	while (data->envp[idx + 1])
	{
		data->envp[idx] = ft_strdup(data->envp[idx + 1]);
		idx++;
	}
}

int	get_index_unset(char **envp, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(tmp, envp[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (-1);
}

int	cmd_unset(t_token *head, t_data *data)
{
	t_token	*tmp;
	int		i;

	if (!head)
		return (1);
	tmp = head->next;
	if (!tmp)
		return (0);
	i = get_index_unset(data->envp, tmp->token);
	if (i != -1)
		remove_env_var(data, i);
	return (0);
}
