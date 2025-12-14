#include "minishell.h"

// int	check_for_pipe(t_token *head)
// {
// 	t_token *current;
// 	int		i;

// 	i = 0;
// 	current = head;
// 	while (current)
// 	{
// 		if(current->type == PIPE)
// 			i++;
// 		current = current->next;
// 	}
// 	return (i);
// }

// ssize_t		find_env(char *env, t_data data)
// {
// 	char	*sub;
// 	ssize_t i;
// 	ssize_t index;

// 	if (!env)
// 		return (-1);
// 	i = 0;
// 	sub = NULL;
// 	while (data->envp[i])
// 	{
// 		if ((index = ft_get_char_by_index(data->envp[i], '=')) == -1)
// 			index = ft_strlen(data->envp[i]);
// 		if ((sub = ft_substr(data->envp[i], 0, index)))
// 		{
// 			if (ft_strequ(sub, env))
// 			{
// 				free(sub);
// 				return (i);
// 			}
// 			free(sub);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

// char	*get_env(char *env, t_data data)
// {
// 	ssize_t i;
// 	size_t	len;

// 	if (!env)
// 		return (NULL);
// 	len = ft_strlen(env);
// 	if ((i = find_env(env, data)) != -1)
// 		return (ft_substr(data->envp[i], (len + 1), ft_strlen(data->envp[i])));
// 	return (NULL);
// }