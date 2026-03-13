/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:54 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 21:06:36 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(int (*fd)[2], int n)
{
	int	i;

	i = -1;
	while (i++ < n - 2)
		if (pipe(fd[i]) == -1)
			exit(1);
}

void	child_process(int i, int (*fd)[2], t_exec *exec)
{
	char	**args;
	char	**clean_args;
	char	*path;
	int		j;

	defauld_signals_in_child();
	if (i > 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i < exec->numofcmd - 2)
		dup2(fd[i][1], STDOUT_FILENO);
	j = -1;
	while (j++ < exec->numofcmd - 2)
	{
		close(fd[j][0]);
		close(fd[j][1]);
	}
	exec_cmd(exec->cmds[i], exec->envp);
}

void	exec_pipes(char **cmds, t_data *data, int numofcmd)
{
	int		(*fd)[2];
	int		pid;
	int		i;
	t_exec	exec;

	exec.cmds = cmds;
	exec.envp = data->envp;
	exec.numofcmd = numofcmd;
	fd = malloc(sizeof(int [2]) * (numofcmd - 2));
	create_pipes(fd, numofcmd);
	i = -1;
	while (i++ < numofcmd - 1)
	{
		pid = fork();
		if (pid == 0)
			child_process(i, fd, &exec);
		ignore_signals_in_parent();
	}
	i = -1;
	while (i++ < numofcmd - 2)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	waitpid(pid, NULL, 0);
}

void	start_pipes(t_token *head, t_data *data, int numofpipes)
{
	char	**cmds;

	cmds = get_cmds(head, numofpipes);
	exec_pipes(cmds, data, numofpipes + 2);
}

void	start_execution(t_token *head, t_data *data)
{
	int	numofpipes;

	numofpipes = check_for_pipes(head);
	if (numofpipes)
		start_pipes(head, data, numofpipes);
	else
		check_for_buildins(head, data);
}
