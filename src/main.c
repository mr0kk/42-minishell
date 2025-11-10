/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:39:07 by rmrok             #+#    #+#             */
/*   Updated: 2025/10/29 19:39:08 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	while (1)
	{
		data->user_input = readline("minishell$ ");
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

void	exit_shell()
{
	printf("wrong usage\n");
	exit(1);
}

void	print_env(char	*env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n\n", env[i]);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;


	// print_env(envp);
	if (!input_check(&data, argc, argv))
		exit_shell(); // add usage error handling
	if (data.interative)
		minishell_interactive(&data, envp);
	else
		minishell_noninteractive();
	return (0);
}