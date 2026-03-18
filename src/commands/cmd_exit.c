/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:10:21 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/17 18:10:22 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	cmd_exit(t_token *head, t_data *data)
{
	t_token	*arg;
	int		exit_code;
	bool	is_piped;

	is_piped = (check_for_pipes(data->head) > 0);
	if (!is_piped)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	arg = head->next;
	if (!arg)
	{
		exit_code = data->last_exit_code;
		if (!is_piped)
		{
			free_all(data);
			rl_clear_history();
		}
		exit(exit_code);
	}
	if (!is_numeric(arg->token))
	{
		char *tmp = ft_strjoin("minishell: exit: ", arg->token);
		char *err_msg = ft_strjoin(tmp, ": numeric argument required\n");
		ft_putstr_fd(err_msg, 2);
		free(tmp);
		free(err_msg);
		if (!is_piped)
		{
			free_all(data);
			rl_clear_history();
		}
		exit(255);
	}
	if (arg->next)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(arg->token);
	if (!is_piped)
	{
		free_all(data);
		rl_clear_history();
	}
	exit((unsigned char)exit_code);
}