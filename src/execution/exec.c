#include "minishell.h"

// void	run_child(t_token head, int pipes[2], int *fd)
// {
// 	close(pipes[0]);
// 	close(0);
// 	dup(*fd);
// 	close(*fd);
// 	if (head->next)
// 	{
// 		close(1);
// 		dup(pipes[1]);
// 		close(pipes[1]);
// 	}
// }

// void	exec_process(t_token head, t_data data, int pipe)
// {
// 	char	*path;
// 	int		cmd_check;

// 	path = get_env("PATH", data);

// }

// int	do_pipe(t_token head, t_data data, int fd)
// {
// 	int	pipes[2];
// 	int pid;

// 	pipes[0] = -1;
// 	pipes[1] = -1;
// 	if (pipe(pipes))
// 		return (-1);
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		close(pipes[0]);
// 		close(pipes[1]);
// 		close(fd);
// 		return -1;
// 	}
// 	else if (!pid)
// 	{
// 		run_child(head, pipes, &fd);
// 		exec_process(head, data, 1);
// 		cmd_exit(head, 0);
// 	}
// 	wait(pid);
// 	child_status();
// 	close(fd);
// 	close(pipes[1]);
// 	return (pipes[0]);
// }

// void	exec_with_pipe(t_token head, t_data data, int *fd)
// {
// 	t_token	*tmp;

// 	while(head)
// 	{
// 		tmp = head;
// 		*fd = do_pipe(head, data, *fd);
// 		head = head->next;
// 	}
// 	close(*fd);
// }

// void	exec_without_pipe(t_token head, t_data data)
// {

// }

// void	start_execution(t_token *head, t_data *data)
// {
// 	int fd;

// 	fd = dup(0);
// 	while (head)
// 	{
// 		if (check_for_pipe(head) > 0)
// 			exec_with_pipe(head, data, &fd);
// 		else
// 			exec_without_pipe(head, data);
// 		head = head->next;
// 	}
// }

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

	while (*ep)
	{
		if (ft_strncmp(*ep, "PATH", 4) == 0)
			break ;
		ep++;
	}
	env_paths = ft_split(*ep + 5, ':');
	if (return_path(env_paths, cmd) == 0)
	{
		free(env_paths);
		return (0);
	}
	else
		return (return_path(env_paths, cmd));
}

int	check_command(char **ep, char *cmd)
{
	char	**env_paths;

	while (*ep)
	{
		if (ft_strncmp(*ep, "PATH", 4) == 0)
			break ;
		ep++;
	}
	env_paths = ft_split(*ep + 5, ':');
	if (return_path(env_paths, cmd) == 0)
	{
		free(env_paths);
		return (1);
	}
	else
		return (0);
}

void	exec_cmd1(int *fd, char *av, char **envp)
{
	char	*arg0;
	char	**args;
	int		fdd;
	int		pid;

	ignore_signals_in_parent();
	pid = fork();
	if (pid == 0)
	{
		defauld_signals_in_child();
		fdd = fd[1];
		args = ft_split(av, ' ');
		if (check_command(envp, args[0]))
		{
			printf("wrong command\n");
			free(args);
			exit(1);
		}
		arg0 = get_path(envp, args[0]);
		close(fd[0]);
		dup2(fdd, 1);
		if (execve(arg0, args, envp) == -1)
		{
			printf("blad execve\n");
			free(arg0);
			free(args);
			exit(1);
		}
		close(fd[1]);
	}
	waitpid(pid, NULL, 0);
}

void	exec_cmd2(int *fd, char *av, char **envp)
{
	char	*arg0;
	char	**args;
	int		fdd;

	fdd = fd[0];
	args = ft_split(av, ' ');
	if (check_command(envp, args[0]))
	{
		printf("wrong command\n");
		free(args);
		exit(1);
	}
	arg0 = get_path(envp, args[0]);
	close(fd[1]);
	dup2(fdd, 0);
	if (execve(arg0, args, envp) == -1)
	{
		printf("blad execve\n");
		free(arg0);
		free(args);
		exit(1);
	}
	close(fd[0]);
}

void	exec_pipes(char **cmds, t_data *data)
{
	int	fd[2];
	int pid;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		exec_cmd2(fd, cmds[1], data->envp);
	else
		exec_cmd1(fd, cmds[0], data->envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
}

int check_for_pipes(t_token *head, t_data *data)
{
	t_token *current;
	char	*commands[2];

	current = head;
	commands[0] = current->token;
	while (current)
	{
		if(current->type == PIPE)
		{
			commands[1] = current->next->token;
			exec_pipes(commands, data);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int start_execution(t_token *head, t_data *data)
{
	if (check_for_pipes(head, data))
		return (1);
	check_for_buildins(head, data);
}

void	exec_cmd(char *av, char **envp)
{
	char	*arg0;
	char	**args;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		args = ft_split(av, ' ');
		if (check_command(envp, args[0]))
		{
			printf("wrong command\n");
			free(args);
			exit(1);
		}
		arg0 = get_path(envp, args[0]);
		if (execve(arg0, args, envp) == -1)
		{
			printf("blad execve\n");
			free(arg0);
			free(args);
			exit(1);
		}
	}
	waitpid(pid, NULL, 0);
}
