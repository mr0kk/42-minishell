#include "minishell.h"

char	*return_path(char **env_paths, char *cmd)
{
	char	*path;
	char	*temp;

	while (*env_paths)
	{
		temp = ft_strjoin(*env_paths, "/");
		path = ft_strjoin(temp, cmd);
		if (access(path, X_OK) == 0)
		{
			free(temp);
			return (path);
		}
		free(temp);
		free(path);
		env_paths++;
	}
	return (NULL);
}

char	*get_path(char **ep, char *cmd)
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
		return (0);
	}
	else
		return (return_path(env_paths, cmd));
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

int check_for_pipes(t_token *head)
{
	t_token *current;
	int		numofpipes;

	current = head;
	numofpipes = 0;
	while (current)
	{
		if(current->type == PIPE)
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

char	**get_cmds(t_token *head, int numofcmds)
{
	t_token *curr;
	char **cmds;
	int i;
	char *tmp;

	curr = head;
	cmds = (char **)calloc(numofcmds + 1, sizeof(char *));
	i = 0;
	while(curr)
	{
		if (curr->type != PIPE)
		{
			tmp = cmds[i];
			cmds[i] = ft_strjoin(tmp, curr->token);
			tmp = cmds[i];
			cmds[i] = ft_strjoin(tmp, " ");
		}
		else
			i++;
		curr = curr->next;
	}
	return (cmds);
}