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

static void	child_process(int i, int (*fd)[2], t_exec *exec, t_data *data)
{
	char	**args;
	char	**clean_args;
	char	*path;
	int		err_code;
	int		j;

	default_signals_in_child();
	if (i > 0)
	{
		if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
		{
			perror("Error on dup2 input");
			exit(EXIT_FAILURE);
		}
	}
	if (i < exec->numofpipes)
	{
		if (dup2(fd[i][1], STDOUT_FILENO) == -1)
		{
			perror("Error on dup2 output");
			exit(EXIT_FAILURE);
		}
	}
	if (exec->numofpipes > 0)
	{
		j = 0;
		while (j < exec->numofpipes)
		{
			close(fd[j][0]);
			close(fd[j][1]);
			j++;
		}
	}
	err_code = exec_cmd(exec->cmds[i], exec->envp, data);
	if (exec->cmds)
		free_string_array(exec->cmds);
	if (data)
		free_all(data);
	if (exec->numofpipes > 0 && fd)
        free(fd);
	exit(err_code);
}

void	exec_pipes(char **cmds, t_data *data, int numofcmd)
{
	int		(*fd)[2];
	int		pid;
	int		i;
	int		status;
	int		last_status;
	t_exec	exec;

	exec.cmds = cmds;
	exec.envp = data->envp;
	exec.numofcmd = numofcmd;
	exec.numofpipes = numofcmd - 1;
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
	else
		fd = NULL;
	i = 0;
	while (i < numofcmd)
	{
		pid = fork();
		if (pid == 0)
			child_process(i, fd, &exec, data);
		ignore_signals_in_parent();
		i++;
	}
	if (exec.numofpipes > 0)
	{
		i = 0;
		while (i < exec.numofpipes)
		{
			close(fd[i][0]);
			close(fd[i][1]);
			i++;
		}
		free(fd);
	}
	i = 0;
	while (i < numofcmd)
	{
		waitpid(-1, &status, WUNTRACED);
		last_status = status;
		i++;
	}
	if (WIFEXITED(status))
		data->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(last_status))
	{
		if (WTERMSIG(last_status) == SIGINT)
			printf("\n");
		else if (WTERMSIG(last_status) == SIGQUIT)
			printf("Quit (core dumped)\n");
		data->last_exit_code = 128 + WTERMSIG(last_status);
	}
	else if (WIFSTOPPED(last_status))
	{
		printf("\n");
		data->last_exit_code = 128 + WSTOPSIG(last_status);
	}
}

void	start_pipes(t_token *head, t_data *data, int numofpipes)
{
	char	**cmds;
	int		i;

	cmds = get_cmds(head, numofpipes + 1);
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
