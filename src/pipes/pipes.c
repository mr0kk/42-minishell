#include "minishell.h"

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
		//ft_free(env_paths);
		return (1);
	}
	else
		return (0);
}

char	*get_ep_path(char **ep, char *cmd)
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
		//ft_free(env_paths);
		return (0);
	}
	else
		return (return_path(env_paths, cmd));
}

int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		exit(1);
	return (ret);
}

void	wrong_command(char *s)
{
	ft_putstr_fd("pipex: command not found :", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	do_read(int *pipe1, char *av, char **envp)
{
	char	*arg0;
	char	**args;
	//int		fd;

	//fd = open_file(av[4], 1);
	args = ft_split(av, ' ');
	if (check_command(envp, av))
	{
		wrong_command(av);
		//ft_free(args);
		exit(127);
	}
	arg0 = get_ep_path(envp, av);
	close(pipe1[1]);
	//dup2(fd, 1);
	dup2(pipe1[0], STDIN_FILENO);
	printf("%s\n", arg0);
	if (execve(arg0, args, envp) == -1)
	{
		printf("TUTAJ read\n");
		free(arg0);
		//ft_free(args);
		exit(1);
	}
	close(pipe1[0]);
}

void	do_write(int *pipe1, char *av, char **envp)
{
	char	*arg0;
	char	**args;
	//int		fd;

	//fd = open_file(av[1], 0);
	args = ft_split(av, ' ');
	if (check_command(envp, av))
	{
		wrong_command(av);
		//ft_free(args);
		exit(127);
	}
	arg0 = get_ep_path(envp, av);
	close(pipe1[0]);
	//dup2(fd, 0);
	dup2(pipe1[1], STDOUT_FILENO);
	printf("%s\n", arg0);
	while(args++)
		printf("%s\n", *args);
	if (execve(arg0, args, envp) == -1)
	{
		printf("TUTAJ write\n");
		free(arg0);
		//ft_free(args);
		exit(1);
	}
	close(pipe1[1]);
}

void	pipes(char **cmds, char **envp)
{
	int	pipe1[2];
	int	pid;

	// if (pipe(pipe1) == -1)
	// 	return (NULL);
	pid = fork();
	// if (pid < 0)
	// 	return (0);
	if (pid == 0)
		do_write(pipe1, cmds[1], envp);
	else
		do_read(pipe1, cmds[0], envp);
	close(pipe1[0]);
	close(pipe1[1]);
	waitpid(pid, NULL, 0);
}