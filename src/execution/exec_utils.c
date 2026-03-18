/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:42 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/17 15:20:46 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(t_token_type type)
{
	return (type == FROM_FILE || type == REPLACE
		|| type == ADD_END || type == HEREDOC);
}

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

static int	count_clean_args(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], ">>", 3) || !ft_strncmp(args[i], ">", 2)
			|| !ft_strncmp(args[i], "<", 2))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**handle_redirections(char **args)
{
	int		i;
	int		j;
	char	**clean;

	clean = ft_calloc(count_clean_args(args) + 1, sizeof(char *));
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], ">>", 3) || !ft_strncmp(args[i], ">", 2))
		{
			i = redir_add_replace(args, i);
			if (i == -1)
				return (free_string_array(clean), NULL);
		}
		else if (!ft_strncmp(args[i], "<", 2))
		{
			i = redir_from_file(args, i);
			if (i == -1)
				return (free_string_array(clean), NULL);
		}
		else
			clean[j++] = ft_strdup(args[i++]);
	}
	return (clean);
}
