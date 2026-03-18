/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:03:26 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/18 16:54:26 by rmrok            ###   ########.fr       */
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
	char	*tmp;
	char	*err_msg;

	if (ft_strchr(clean_args[0], '/'))
	{
		path = ft_strdup(clean_args[0]);
		if (access(path, F_OK) != 0)
			handle_nofile(path);
	}
	else
	{
		path = get_path(envp, clean_args[0]);
		if (!path)
		{
			tmp = ft_strjoin("minishell: ", clean_args[0]);
			err_msg = ft_strjoin(tmp, ": command not found\n");
			ft_putstr_fd(err_msg, 2);
			free(tmp);
			free(err_msg);
		}
	}
	return (path);
}

int	handle_path(char **clean_args, char **envp)
{
	char	*path;

	path = get_valid_path(clean_args, envp);
	if (!path)
	{
		free_string_array(clean_args);
		return (127);
	}
	if (execve(path, clean_args, envp) == -1)
	{
		perror("minishell");
		free_string_array(clean_args);
		free(path);
		return (126);
	}
	return (0);
}

int	exec_cmd(char *av, char **envp, t_data *data)
{
	char	**clean_args;
	t_token	*temp_list;
	int		exit_code;

	clean_args = prepare_args(av);
	if (!clean_args)
		return (1);
	remove_quotes(clean_args);
	temp_list = argv_to_token_list(clean_args);
	if (is_builtin(temp_list))
	{
		exit_code = run_correct_cmd(temp_list, data);
		free_tokens(&temp_list);
		free_string_array(clean_args);
		return (exit_code);
	}
	free_tokens(&temp_list);
	return (handle_path(clean_args, envp));
}
