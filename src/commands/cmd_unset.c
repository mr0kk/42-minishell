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

static bool	is_valid_identifier(char *var)
{
	int	i;

	i = 0;
	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (false);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

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

int	cmd_unset(t_token *head, t_data *data)
{
	t_token	*tmp;
	int		i;
	int		exit_status;

	exit_status = 0;
	tmp = head->next;
	while (tmp)
	{
		if (!is_valid_identifier(tmp->token))
		{
			char *tmp1 = ft_strjoin("minishell: unset: `", tmp->token);
			char *err_msg = ft_strjoin(tmp1, "': not a valid identifier\n");
			ft_putstr_fd(err_msg, 2);
			free(tmp1);
			free(err_msg);
			exit_status = 1;
		}
		else
		{
			i = get_var_index(data->envp, tmp->token);
			if (i != -1)
				remove_env_var(data, i);
		}
		tmp = tmp->next;
	}
	return (exit_status);
}
