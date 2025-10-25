#include "minishell.h"

void	print_tokens(char **instructions)
{
	int	i;

	i = 0;
	while (instructions[i])
	{
		printf("%s\n", instructions[i]);
		i++;
	}
}