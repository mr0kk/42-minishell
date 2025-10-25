/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:47:27 by rmrok             #+#    #+#             */
/*   Updated: 2025/10/22 20:47:28 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	minishell_interactive(t_data *data)
{
	while (1)
	{
		data->user_input = readline("minishell$ ");
		if (!ft_strncmp(data->user_input, "exit", 5))
		{
			free_data(data);
			break;
		}
		input_handler(data);
		free(data->user_input);
	}
}

void	minishell_noninteractive()
{
	printf("noninteractive in progress\n");
}

void	exit_shell()
{
	printf("wrong usage\n");
	exit(1);
}

int main(int argc, char *argv[], char *env[])
{
	t_data	data;

	if (!input_check(&data, argc, argv))
		exit_shell();
	if (data.interative)
		minishell_interactive(&data);
	else
		minishell_noninteractive();
	return (0);
}