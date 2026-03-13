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
		defauld_signals_in_child();
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
		defauld_signals_in_child();
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

void	exec_cmd(char *av, char **envp)
{
	char	**args;
	char	**clean_args;
	char	*path;

	args = ft_split(av, ' ');
	clean_args = handle_redirections(args);
	if (check_command(envp, clean_args[0]))
	{
		printf("wrong command\n");
		exit(1);
	}
	path = get_path(envp, clean_args[0]);
	if (execve(path, clean_args, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}
