/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:03:26 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 21:05:12 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_single_child(char **cmds, t_data *data)
{
	int	exit_code;

	default_signals_in_child();
	if (!cmds[0])
	{
		free_string_array(cmds);
		free_all(data);
		exit(0);
	}
	exit_code = exec_cmd(cmds[0], data->envp, data);
	free_string_array(cmds);
	free_all(data);
	exit(exit_code);
}

void	exec_single_command(t_token *head, t_data *data)
{
	pid_t	pid;
	char	**cmds;

	cmds = get_cmds(head, 1, 0);
	if (!cmds)
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		data->last_exit_code = 1;
		free_string_array(cmds);
		return ;
	}
	if (pid == 0)
		execute_single_child(cmds, data);
	ignore_signals_in_parent();
	wait_single_child(pid, data);
	free_string_array(cmds);
}

static char	*get_valid_path(char **clean_args, char **envp)
{
	char	*path;

	if (ft_strchr(clean_args[0], '/'))
	{
		path = ft_strdup(clean_args[0]);
		if (access(path, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			free(path);
			return (NULL);
		}
	}
	else
	{
		path = get_path(envp, clean_args[0]);
		if (!path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(clean_args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
	return (path);
}

static char	**prepare_args(char *av, char ***args)
{
	char	**clean_args;

	if (!av || !av[0])
		return (NULL);
	*args = ft_split(av, ' ');
	if (!*args)
		exit_shell("Memory allocation error");
	if (!(*args)[0])
	{
		free_string_array(*args);
		return (NULL);
	}
	clean_args = handle_redirections(*args);
	if (!clean_args || !clean_args[0])
	{
		free_2arrays_and_str(*args, clean_args, NULL);
		return (NULL);
	}
	return (clean_args);
}

int	exec_cmd(char *av, char **envp, t_data *data)
{
	char	**args;
	char	**clean_args;
	char	*path;

	(void)data;
	clean_args = prepare_args(av, &args);
	if (!clean_args)
		return (0);
	path = get_valid_path(clean_args, envp);
	if (!path)
	{
		free_2arrays_and_str(args, clean_args, NULL);
		return (127);
	}
	if (execve(path, clean_args, envp) == -1)
	{
		perror("minishell");
		free_2arrays_and_str(args, clean_args, path);
		return (126);
	}
	return (0);
}
