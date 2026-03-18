/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:55:21 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/18 16:55:23 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_identifier(char *var)
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

void	unset_export_error(char *token, int *exit_status, char *cmd)
{
	char	*tmp1;
	char	*err_msg;

	if (ft_strncmp(cmd, "export", 7) == 0)
		tmp1 = ft_strjoin("minishell: export: `", token);
	else
		tmp1 = ft_strjoin("minishell: unset: `", token);
	err_msg = ft_strjoin(tmp1, "': not a valid identifier\n");
	ft_putstr_fd(err_msg, 2);
	free(tmp1);
	free(err_msg);
	*exit_status = 1;
}

void	sort_string_array(char **arr, int count)
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

void	print_single_export_line(char *env_var)
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

void	print_export(t_data *data)
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
