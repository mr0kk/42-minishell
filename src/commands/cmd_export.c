/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:11 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 13:59:53 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index_export(char **envp, char *var)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while (var[j] && var[j] != '=')
		j++;
	if (var[j] != '=')
		return (-1);
	tmp = ft_substr(var, 0, j + 1);
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

void	cmd_export(t_token *head, t_data *data)
{
	t_token	*tmp;
	int		i;
	int		count;
	char	**new_envp;

	if (!head)
		return ;
	tmp = head->next;
	while (tmp)
	{
		if (ft_strchr(tmp->token, '='))
		{
			i = get_index_export(data->envp, tmp->token);
			if (i != -1)
			{
				free(data->envp[i]);
				data->envp[i] = ft_strdup(tmp->token);
			}
			else
			{
				count = 0;
				while (data->envp[count])
					count++;
				new_envp = ft_calloc(count + 2, sizeof(char *));
				if (!new_envp)
					exit_shell("Memory allocation error");
				i = 0;
				while (i < count)
				{
					new_envp[i] = data->envp[i];
					i++;
				}
				new_envp[i] = ft_strdup(tmp->token);
				free(data->envp);
				data->envp = new_envp;
			}
		}
		tmp = tmp->next;
	}
}
