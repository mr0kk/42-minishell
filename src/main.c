/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:22:07 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/17 15:22:08 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_pid = 0;

/*
	This function checks amount of arguments given when program starts
	For none args sets to run interactive minshell 
	in case of 3 args sets to run noninteractive minishell
	otherwise gives usegage error
*/
int	input_check(t_data *data, int argc, char **argv)
{
	if (argc == 1 && argv[0])
	{
		data->interative = 1;
		return (1);
	}
	data->interative = 0;
	return (0);
}

void	free_data(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
}

void	minishell_interactive(t_data *data)
{
	while (1)
	{
		init_signals();
		data->user_input = readline("minishell$ ");
		if (!data->user_input)
		{
			printf("exit\n");
			free(data->user_input);
			rl_clear_history();
			break ;
		}
		if (data->user_input[0] != '\0')
			add_history(data->user_input);
		input_handler(data);
		free(data->user_input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.last_exit_code = 0;
	add_env(&data, envp);
	if (!input_check(&data, argc, argv))
		exit_shell("Wrong usage");
	if (data.interative)
		minishell_interactive(&data);
	rl_clear_history();
	free_env(&data);
	return (0);
}
