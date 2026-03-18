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

static int	get_var_index(char **envp, char *var)
{
	int		i;
	size_t	var_len;

	var_len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, var_len) == 0
			&& (envp[i][var_len] == '=' || envp[i][var_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static void	remove_env_var(t_data *data, int idx_to_remove)
{
	int		count;
	char	**new_envp;
	int		i;
	int		j;

	count = 0;
	while (data->envp[count])
		count++;
	new_envp = ft_calloc(count, sizeof(char *));
	if (!new_envp)
		exit_shell("Memory allocation error");
	i = -1;
	j = 0;
	while (++i < count)
	{
		if (i != idx_to_remove)
			new_envp[j++] = data->envp[i];
		else
			free(data->envp[i]);
	}
	free(data->envp);
	data->envp = new_envp;
}

static void	handle_valid_unset(t_data *data, char *token)
{
	int	i;

	i = get_var_index(data->envp, token);
	if (i != -1)
		remove_env_var(data, i);
}

int	cmd_unset(t_token *head, t_data *data)
{
	t_token	*tmp;
	int		exit_status;

	exit_status = 0;
	tmp = head->next;
	while (tmp)
	{
		if (!is_valid_identifier(tmp->token))
			unset_export_error(tmp->token, &exit_status, "unset");
		else
			handle_valid_unset(data, tmp->token);
		tmp = tmp->next;
	}
	return (exit_status);
}
