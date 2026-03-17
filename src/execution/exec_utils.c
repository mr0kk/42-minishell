/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:42 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 21:07:10 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*path;

	if (!ep || !cmd)
		return (NULL);
	while (*ep)
	{
		if (ft_strncmp(*ep, "PATH", 4) == 0)
			break ;
		ep++;
	}
	if (!*ep)
		return (NULL);
	env_paths = ft_split(*ep + 5, ':');
	path = return_path(env_paths, cmd);
	free_string_array(env_paths);
	return (path);
}

char	**get_cmds(t_token *head, int numofcmds, int i)
{
	t_token	*curr;
	char	**cmds;
	char	*tmp;

	curr = head;
	cmds = (char **)ft_calloc(numofcmds + 1, sizeof(char *));
	if (!cmds)
		return (NULL);
	while (curr)
	{
		if (curr->type != PIPE)
		{
			tmp = cmds[i];
			cmds[i] = ft_strjoin(tmp, curr->token);
			free(tmp);
			tmp = cmds[i];
			cmds[i] = ft_strjoin(tmp, " ");
			free(tmp);
		}
		else
			i++;
		curr = curr->next;
	}
	return (cmds);
}

char	**handle_redirections(char **args)
{
	int		i;
	int		j;
	char	**clean;

	clean = malloc(sizeof(char *) * 100); // no free after this malloc
	i = 0;
	j = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], ">>", 3) || !ft_strncmp(args[i], ">", 2))
			i = redir_add_replace(args, i);
		else if (!ft_strncmp(args[i], "<", 2))
			i = redir_from_file(args, i);
		else
			clean[j++] = ft_strdup(args[i++]);
	}
	clean[j] = NULL;
	return (clean);
}
