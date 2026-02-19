/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:39:07 by rmrok             #+#    #+#             */
/*   Updated: 2026/02/19 22:47:20 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal_pid = 0;

/*
	This function checks amount of arguments given when program starts
	For none args sets to run interactive minshell 
	in case of 3 args sets to run noninteractive minishell
	otherwise gives usegage error
*/
int	input_check(t_data *data, int argc, char **argv)
{
	if (argc == 1)
		data->interative = 1;
	else if (argc == 3)
		data->interative = 0;
	else
		return (0);
	return (1);
}	

void	free_data(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
}


/*
	runs interactiove verstion of minishell
	func handle instruction given in input line then frees
	memory after proceding input
*/
void	minishell_interactive(t_data *data, char **envp)
{
	init_signals();
	while (1)
	{
		data->user_input = readline("minishell$ ");
		if (!data->user_input)
		{
			free(data->user_input);
			rl_clear_history();
			break;
		}
		if (data->user_input[0] != '\0')
			add_history(data->user_input);
		if (!ft_strncmp(data->user_input, "exit", 5))
		{
			free(data->user_input);
			break;
		}
		input_handler(data, envp);
		free(data->user_input);
	}
}

void	minishell_noninteractive()
{
	printf("noninteractive in progress\n");
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.last_exit_code = 0;
	add_env(&data, envp);
	if (!input_check(&data, argc, argv))
		exit_shell("Wrong usage"); // add usage error handling
	if (data.interative)
		minishell_interactive(&data, envp);
	else
		minishell_noninteractive();
	rl_clear_history();
	return (0);
}