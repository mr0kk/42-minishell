#include "minishell.h"

void	cmd_env(t_data *data)
{
	int i;

	i = 0;
	while(data->envp[i])
		ft_putendl_fd(data->envp[i++], STDOUT_FILENO);
}