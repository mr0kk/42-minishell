
#include "minishell.h"

void	wait_single_child(pid_t pid, t_data *data)
{
	int	status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		data->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
		else if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
		data->last_exit_code = 128 + WTERMSIG(status);
	}
	else if (WIFSTOPPED(status))
	{
		printf("\n");
		data->last_exit_code = 128 + WSTOPSIG(status);
	}
}

void	setup_child_pipes(int i, int (*fd)[2], t_exec *exec)
{
	int	j;

	if (i > 0 && dup2(fd[i - 1][0], STDIN_FILENO) == -1)
	{
		perror("Error on dup2 input");
		exit(EXIT_FAILURE);
	}
	if (i < exec->numofpipes && dup2(fd[i][1], STDOUT_FILENO) == -1)
	{
		perror("Error on dup2 output");
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (exec->numofpipes > 0 && j < exec->numofpipes)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

void	wait_for_children(t_data *data, int numofcmd, int last_pid)
{
	int	i;
	int	pid;
	int	status;
	int	last_status;

	i = 0;
	while (i < numofcmd)
	{
		pid = waitpid(-1, &status, WUNTRACED);
		if (pid == last_pid)
			last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		data->last_exit_code = WEXITSTATUS(last_status);
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

void	child_process(int i, int (*fd)[2], t_exec *exec, t_data *data)
{
	int		err_code;

	default_signals_in_child();
	setup_child_pipes(i, fd, exec);
	err_code = exec_cmd(exec->cmds[i], exec->envp, data);
	if (exec->cmds)
		free_string_array(exec->cmds);
	if (data)
		free_all(data);
	if (exec->numofpipes > 0 && fd)
		free(fd);
	exit(err_code);
}
