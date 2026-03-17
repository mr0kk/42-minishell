/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:54 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/17 15:20:49 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_pipes(int (*fd)[2], int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("pipe error");
			while (--i >= 0)
			{
				close(fd[i][0]);
				close(fd[i][1]);
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

int	handle_processes(t_data *data, t_exec *exec, int (*fd)[2])
{
	int	i;
	int	pid;

	i = 0;
	while (i < exec->numofcmd)
	{
		pid = fork();
		if (pid == 0)
			child_process(i, fd, exec, data);
		ignore_signals_in_parent();
		i++;
	}
	if (exec->numofpipes > 0)
	{
		i = 0;
		while (i < exec->numofpipes)
		{
			close(fd[i][0]);
			close(fd[i][1]);
			i++;
		}
		free(fd);
	}
	return (pid);
}

void	exec_pipes(char **cmds, t_data *data, int numofcmd)
{
	int		(*fd)[2];
	t_exec	exec;
	int		last_pid;

	exec.cmds = cmds;
	exec.envp = data->envp;
	exec.numofcmd = numofcmd;
	exec.numofpipes = numofcmd - 1;
	fd = NULL;
	if (exec.numofpipes > 0)
	{
		fd = malloc(sizeof(int [2]) * exec.numofpipes);
		if (!fd)
			return ;
		if (create_pipes(fd, exec.numofpipes) == -1)
		{
			free(fd);
			return ;
		}
	}
	last_pid = handle_processes(data, &exec, fd);
	wait_for_children(data, numofcmd, last_pid);
}

void	start_pipes(t_token *head, t_data *data, int numofpipes)
{
	char	**cmds;
	int		i;

	cmds = get_cmds(head, numofpipes + 1, 0);
	if (!cmds)
		return ;
	exec_pipes(cmds, data, numofpipes + 1);
	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
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
