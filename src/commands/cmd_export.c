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

static bool	is_valid_identifier(char *var)
{
	int	i;

	i = 0;
	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (false);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	sort_string_array(char **arr, int count)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			k = 0;
			while (arr[j][k] && arr[j][k] == arr[j + 1][k])
				k++;
			if ((unsigned char)arr[j][k] > (unsigned char)arr[j + 1][k])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

static void	print_single_export_line(char *env_var)
{
	int	j;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	j = 0;
	while (env_var[j] && env_var[j] != '=')
		ft_putchar_fd(env_var[j++], STDOUT_FILENO);
	if (env_var[j] == '=')
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(env_var + j + 1, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	print_export(t_data *data)
{
	int		i;
	int		count;
	char	**env_copy;

	count = 0;
	while (data->envp[count])
		count++;
	env_copy = ft_calloc(count + 1, sizeof(char *));
	if (!env_copy)
		return ;
	i = -1;
	while (++i < count)
		env_copy[i] = data->envp[i];
	sort_string_array(env_copy, count);
	i = -1;
	while (++i < count)
		print_single_export_line(env_copy[i]);
	free(env_copy);
}

int	get_index_export(char **envp, char *var)
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

static void	update_or_add_env(t_data *data, char *token)
{
	int		i;
	int		count;
	char	**new_envp;

	i = get_index_export(data->envp, token);
	if (i != -1)
	{
		free(data->envp[i]);
		data->envp[i] = ft_strdup(token);
		if (!data->envp[i])
			exit_shell("Memory allocation error");
		return ;
	}
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
	free(data->envp);
	data->envp = new_envp;
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
		{
			char *tmp1 = ft_strjoin("minishell: export: `", tmp->token);
			char *err_msg = ft_strjoin(tmp1, "': not a valid identifier\n");
			ft_putstr_fd(err_msg, 2);
			free(tmp1);
			free(err_msg);
			exit_status = 1;
		}
		else if (ft_strchr(tmp->token, '='))
			update_or_add_env(data, tmp->token);
		tmp = tmp->next;
	}
	return (exit_status);
}
