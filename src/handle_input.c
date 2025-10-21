#include "../include/minishell.h"

// returns 1 if valid, 0 if not
int	input_valid(t_data *data, int argc, char **argv)
{
	if (argc == 1)
		data->interative = 1;
	else
		data->interative = 0;
	return (1);
}	