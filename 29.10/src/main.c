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

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (!input_check(&data, argc, argv))
		exit_shell();
	if (data.interative)
		minishell_interactive(&data, envp);
	else
		minishell_noninteractive();
	return (0);
}