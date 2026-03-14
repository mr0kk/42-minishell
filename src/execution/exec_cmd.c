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

// void	exec_cmd_withoutpipe(t_token *head, char *av, char **envp)
// {
// 	char	*arg0;
// 	char	*tmp;
// 	char	**args;
// 	int		pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		default_signals_in_child();
// 		tmp = *get_cmds(head, 0);
// 		args = ft_split(tmp, ' ');
// 		check(envp, args[0]);
// 		arg0 = get_path(envp, args[0]);
// 		if (execve(arg0, args, envp) == -1)
// 		{
// 			printf("blad execve\n");
// 			free(arg0);
// 			free(args);
// 			exit(1);
// 		}
// 	}
// 	ignore_signals_in_parent();
// 	waitpid(pid, NULL, 0);
// }

void	exec_single_command(t_token *head, t_data *data)
{
	pid_t	pid;
	int		status;
	char	**cmds;
	int		exit_code;

	cmds = get_cmds(head, 1);
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
	{
		default_signals_in_child();
		if(!cmds[0])
			exit(0);
		exit_code = exec_cmd(cmds[0], data->envp, data);
		free_string_array(cmds);
		exit(exit_code);
	}
	ignore_signals_in_parent();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->last_exit_code = 128 + WTERMSIG(status);
	free_string_array(cmds);
}

// void	exec_cmd_absolutepath_withoutpipe(char *av, char **envp)
// {
// 	char	**args;
// 	char	*tmp;
// 	int		pid;
// 	int		i;

// 	i = 0;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		default_signals_in_child();
// 		args = ft_split(av, '/');
// 		while (args[i])
// 			i++;
// 		tmp = ft_strdup(args[i - 1]);
// 		args = ft_split(tmp, ' ');
// 		check(envp, args[0]);
// 		if (execve(av, args, envp) == -1)
// 		{
// 			printf("blad execve\n");
// 			free(args);
// 			exit(1);
// 		}
// 	}
// 	ignore_signals_in_parent();
// 	waitpid(pid, NULL, 0);
// }

int	exec_cmd(char *av, char **envp, t_data *data)
{
	char	**args;
	char	**clean_args;
	char	*path;

	if (!av || !av[0])
		return (0);
	args = ft_split(av, ' ');
	if (!args || !args[0])
		exit_shell("Memory allocation error");
	clean_args = handle_redirections(args);
	if (!clean_args || !clean_args[0])
	{
		free_string_array(args);
		if (clean_args)
			free_string_array(clean_args);
		return (0);
	}
	if (ft_strchr(clean_args[0], '/'))	
	{
		path = ft_strdup(clean_args[0]);
		if (access(path, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			free(path);
			free_string_array(args);
			free_string_array(clean_args);
			return (127);
		}		
	}
	else
		path = get_path(envp, clean_args[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(clean_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_string_array(args);
		free_string_array(clean_args);
		return (127);
	}
	if (execve(path, clean_args, envp) == -1)
	{
		perror("minishell");
		free(path);
		free_string_array(args);
		free_string_array(clean_args);
		return (126);
	}
	free(path);
	free_string_array(args);
	free_string_array(clean_args);
	return (0);
}
