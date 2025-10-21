#include "../include/minishell.h"

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
		printf("%s\n", data->user_input);
		free(data->user_input);
	}
}

void	minishell_noninteractive()
{
	printf("noninteractive in progress\n");
}

void	exit_shell()
{
	printf("exit shell\n");
	exit(1);
}

int main(int argc, char *argv[], char *env[])
{
	t_data	data;

	if (!input_valid(&data, argc, argv))
		exit_shell();
	if (data.interative)
		minishell_interactive(&data);
	else
		minishell_noninteractive();
	
	return (0);
}