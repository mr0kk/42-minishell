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

void	exec_cmd_withoutpipe(t_token *head, char *av, char **envp)
{
	char	*arg0;
	char	*tmp;
	char	**args;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		default_signals_in_child();
		tmp = *get_cmds(head, 0);
		args = ft_split(tmp, ' ');
		check(envp, args[0]);
		arg0 = get_path(envp, args[0]);
		if (execve(arg0, args, envp) == -1)
		{
			printf("blad execve\n");
			free(arg0);
			free(args);
			exit(1);
		}
	}
	ignore_signals_in_parent();
	waitpid(pid, NULL, 0);
}

void	exec_cmd_absolutepath_withoutpipe(char *av, char **envp)
{
	char	**args;
	char	*tmp;
	int		pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		default_signals_in_child();
		args = ft_split(av, '/');
		while (args[i])
			i++;
		tmp = ft_strdup(args[i - 1]);
		args = ft_split(tmp, ' ');
		check(envp, args[0]);
		if (execve(av, args, envp) == -1)
		{
			printf("blad execve\n");
			free(args);
			exit(1);
		}
	}
	ignore_signals_in_parent();
	waitpid(pid, NULL, 0);
}

int	exec_cmd(char *av, char **envp, t_data *data)
{
	char	**args;
	char	**clean_args;
	char	*path;

	if (!av || !av[0])
		return (0);
	args = ft_split(av, ' ');
	clean_args = handle_redirections(args);
	if (!clean_args || !clean_args[0])
	{
		free_string_array(args);
		if (clean_args)
			free_string_array(clean_args);
		return (0);
	}
	if (check_command(envp, clean_args[0]))
	{
		printf("wrong command\n");
		free_string_array(args);
		free_string_array(clean_args);
		return (126);
	}
	path = get_path(envp, clean_args[0]);
	if (execve(path, clean_args, envp) == -1)
	{
		perror("execve");
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
