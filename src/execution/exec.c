#include "minishell.h"

void exec_cmd_withoutpipe(t_token *head, char *av, char **envp)
{
	char	*arg0;
	char	*tmp;
	char	**args;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		tmp = *get_cmds(head, 0);
		args = ft_split(tmp, ' ');
		if (check_command(envp, args[0]))
		{
			printf("wrong command %s\n", args[0]);
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

void exec_cmd_absolutepath_withoutpipe(char *av, char **envp)
{
	char	**args;
	char	*tmp;
	int		pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		args = ft_split(av, '/');
		while (args[i])
			i++;
		tmp = ft_strdup(args[i - 1]);
		args = ft_split(tmp, ' ');
		if (check_command(envp, args[0]))
		{
			printf("wrong command\n");
			free(args);
			exit(1);
		}
		if (execve(av, args, envp) == -1)
		{
			printf("blad execve\n");
			free(args);
			exit(1);
		}
	}
	waitpid(pid, NULL, 0);
}

char	*check_absolute_path(char *av, char **envp)
{
	char *temp;
	int i;
	char **args;
	char *arg0;

	i = 0;
	args = ft_split(av, '/');
	while (args[i])
		i++;
	temp = ft_strdup(args[i - 1]);
	args = ft_split(temp, ' ');
	arg0 = get_path(envp, args[0]);
	av = ft_strtrim(av, " ");
	if (!ft_strncmp(av, arg0, ft_strlen(arg0)))
		return (temp);
	else
	{
		printf("no such file or directory: %s", av);
		free(temp);
		free(args);
		free(arg0);
		exit (1);
	}
}

void exec_cmd(char *av, char **envp)
{
	char	*arg0;
	char	**args;

	if (av[0] == '/')
		av = check_absolute_path(av, envp);
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

void	exec_pipes(char **cmds, t_data *data, int numofcmd)
{
	int	fd[numofcmd - 2][2];
	int pid;
	int i;
	int j;

	i = 0;
	while (i < numofcmd - 2)
	{
		if (pipe(fd[i]) == -1)
			exit(1);
		i++;
	}
	i = 0;
	while (i < numofcmd - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
				dup2(fd[i - 1][0], STDIN_FILENO);
			if (i < numofcmd - 2)
				dup2(fd[i][1], STDOUT_FILENO);
			j = 0;
			while (j < numofcmd - 2)
			{
				close(fd[j][0]);
				close(fd[j][1]);
				j++;
			}
			exec_cmd(cmds[i], data->envp);
		}
		i++;
	}
	i = 0;
	while (i < numofcmd - 2)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	waitpid(pid, NULL, 0);
}

void	start_pipes(t_token *head, t_data *data, int numofpipes)
{

	char **cmds;

	cmds = get_cmds(head, numofpipes);

	exec_pipes(cmds, data, numofpipes + 2);
}

void start_execution(t_token *head, t_data *data)
{
	int	numofpipes;

	numofpipes = check_for_pipes(head);
	if (numofpipes)
		start_pipes(head, data, numofpipes);
	else 
		check_for_buildins(head, data);
}