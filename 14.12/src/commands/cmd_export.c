#include "minishell.h"

int	get_index_export(char **envp, char *var)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while(var[j] != '=')
		j++;
	tmp = ft_substr(var, 0, j + 1);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(tmp, envp[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (-1);
}

void cmd_export(t_token *head, t_data *data)
{
	t_token	*tmp;
	int		i;

	if (!head)
		return ;
	tmp = head->next;
	i = get_index_export(data->envp, tmp->token);
	if (i != -1)
		data->envp[i] = ft_strdup(tmp->token);
}