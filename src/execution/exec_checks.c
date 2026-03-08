/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:04:40 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 21:07:16 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_pipes(t_token *head)
{
	t_token	*current;
	int		numofpipes;

	current = head;
	numofpipes = 0;
	while (current)
	{
		if (current->type == PIPE || current->type == REPLACE
			|| current->type == FROM_FILE || current->type == ADD_END)
			numofpipes++;
		current = current->next;
	}
	return (numofpipes);
}

void	check_for_buildins(t_token *head, t_data *data)
{
	if (ft_strncmp(head->token, "cd", 3) == 0)
		cmd_cd(head);
	else if (ft_strncmp(head->token, "echo", 5) == 0)
		cmd_echo(head);
	else if (ft_strncmp(head->token, "env", 4) == 0)
		cmd_env(data);
	else if (ft_strncmp(head->token, "export", 7) == 0)
		cmd_export(head, data);
	else if (ft_strncmp(head->token, "pwd", 4) == 0)
		cmd_pwd(head);
	else if (ft_strncmp(head->token, "unset", 6) == 0)
		cmd_unset(head, data);
	else if (ft_strncmp(head->token, "exit", 5) == 0)
		cmd_exit(head);
	else if (ft_strncmp(head->token, "/", 1) == 0)
		exec_cmd_absolutepath_withoutpipe(head->token, data->envp);
	else
		exec_cmd_withoutpipe(head, head->token, data->envp);
}

int	check_command(char **ep, char *cmd)
{
	char	**env_paths;

	while (*ep)
	{
		if (ft_strncmp(*ep, "PATH", 4) == 0)
			break ;
		ep++;
	}
	env_paths = ft_split(*ep + 5, ':');
	if (return_path(env_paths, cmd) == 0)
	{
		free(env_paths);
		return (1);
	}
	else
		return (0);
}

char	*check_absolute_path(char *av, char **envp)
{
	char	*temp;
	int		i;
	char	**args;
	char	*arg0;

	i = 0;
	args = ft_split(av, '/');
	while (args[i])
		i++;
	temp = ft_strdup(args[i - 1]);
	args = ft_split(temp, ' ');
	arg0 = get_path(envp, args[0]);
	av = ft_strtrim(av, " ");
	if (!ft_strncmp(av, arg0, ft_strlen(arg0)))
		return (temp);
	else
	{
		printf("no such file or directory: %s", av);
		free(temp);
		free(args);
		free(arg0);
		exit (1);
	}
}
