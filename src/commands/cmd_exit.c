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

static void	cleanup_and_exit(t_data *data, int exit_code, bool is_piped)
{
	if (!is_piped)
	{
		free_all(data);
		rl_clear_history();
	}
	exit(exit_code);
}

static void	exit_numeric_error(t_data *data, char *arg_token, bool is_piped)
{
	char	*tmp;
	char	*err_msg;

	tmp = ft_strjoin("minishell: exit: ", arg_token);
	err_msg = ft_strjoin(tmp, ": numeric argument required\n");
	ft_putstr_fd(err_msg, 2);
	free(tmp);
	free(err_msg);
	cleanup_and_exit(data, 255, is_piped);
}

int	cmd_exit(t_token *head, t_data *data)
{
	t_token	*arg;
	bool	is_piped;

	is_piped = (check_for_pipes(data->head) > 0);
	if (!is_piped)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	arg = head->next;
	if (!arg)
		cleanup_and_exit(data, data->last_exit_code, is_piped);
	if (!is_numeric(arg->token))
		exit_numeric_error(data, arg->token, is_piped);
	if (arg->next)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	cleanup_and_exit(data, (unsigned char)ft_atoi(arg->token), is_piped);
	return (0);
}
