/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:55:41 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/18 16:55:43 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_index_export(char **envp, char *var)
{
	int		i;
	int		var_len;

	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
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

static void	add_new_env_var(t_data *data, char *token)
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	while (data->envp[count])
		count++;
	new_envp = ft_calloc(count + 2, sizeof(char *));
	if (!new_envp)
		exit_shell("Memory allocation error");
	i = -1;
	while (++i < count)
		new_envp[i] = data->envp[i];
	new_envp[count] = ft_strdup(token);
	if (!new_envp[count])
	{
		free(new_envp);
		exit_shell("Memory allocation error");
	}
	free(data->envp);
	data->envp = new_envp;
}

static void	update_or_add_env(t_data *data, char *token)
{
	int		i;

	i = get_index_export(data->envp, token);
	if (i != -1)
	{
		free(data->envp[i]);
		data->envp[i] = ft_strdup(token);
		if (!data->envp[i])
			exit_shell("Memory allocation error");
	}
	else
		add_new_env_var(data, token);
}

int	cmd_export(t_token *head, t_data *data)
{
	t_token	*tmp;
	int		exit_status;

	exit_status = 0;
	tmp = head->next;
	if (!tmp)
	{
		print_export(data);
		return (0);
	}
	while (tmp)
	{
		if (!is_valid_identifier(tmp->token))
			unset_export_error(tmp->token, &exit_status, "export");
		else if (ft_strchr(tmp->token, '='))
			update_or_add_env(data, tmp->token);
		tmp = tmp->next;
	}
	return (exit_status);
}
