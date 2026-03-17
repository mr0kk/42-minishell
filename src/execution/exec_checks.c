/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:04:40 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/17 15:20:40 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_redir_fd(t_token *curr)
{
	int	fd;
	int	flags;

	if (curr->type == REPLACE || curr->type == ADD_END)
	{
		flags = O_WRONLY | O_CREAT;
		if (curr->type == REPLACE)
			flags |= O_TRUNC;
		else
			flags |= O_APPEND;
		fd = open(curr->next->token, flags, 0644);
		if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
			return (perror("minishell"), 1);
		close(fd);
	}
	else if (curr->type == FROM_FILE)
	{
		fd = open(curr->next->token, O_RDONLY);
		if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
			return (perror("minishell"), 1);
		close(fd);
	}
	return (0);
}

static int	apply_redirections(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		if (is_redir(curr->type) && curr->next)
		{
			if (setup_redir_fd(curr) != 0)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	run_correct_cmd(t_token *head, t_data *data)
{
	if (ft_strncmp(head->token, "cd", 3) == 0)
		return (cmd_cd(head));
	else if (ft_strncmp(head->token, "echo", 5) == 0)
		return (cmd_echo(head));
	else if (ft_strncmp(head->token, "env", 4) == 0)
		return (cmd_env(data));
	else if (ft_strncmp(head->token, "export", 7) == 0)
		return (cmd_export(head, data));
	else if (ft_strncmp(head->token, "pwd", 4) == 0)
		return (cmd_pwd(head));
	else if (ft_strncmp(head->token, "unset", 6) == 0)
		return (cmd_unset(head, data));
	else if (ft_strncmp(head->token, "exit", 5) == 0)
		exit(0);
	return (0);
}

void	check_for_buildins(t_token *head, t_data *data)
{
	int	stdout_backup;
	int	stdin_backup;
	int	exit_code;

	if (is_builtin(head))
	{
		stdout_backup = dup(STDOUT_FILENO);
		stdin_backup = dup(STDIN_FILENO);
		if (apply_redirections(head) != 0)
		{
			dup2(stdin_backup, STDIN_FILENO);
			dup2(stdout_backup, STDOUT_FILENO);
			close(stdin_backup);
			close(stdout_backup);
			return ;
		}
		exit_code = run_correct_cmd(head, data);
		data->last_exit_code = exit_code;
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
	}
	else
		exec_single_command(head, data);
}

char	*check_absolute_path(char *av, char **envp)
{
	char	*temp;
	int		i;
	char	**args;
	char	*arg0;

	i = 0;
	args = ft_split(av, '/');
	while (args[i])
		i++;
	temp = ft_strdup(args[i - 1]);
	free_string_array(args);
	arg0 = get_path(envp, temp);
	av = ft_strtrim(av, " ");
	if (!ft_strncmp(av, arg0, ft_strlen(arg0)))
		return (temp);
	else
	{
		printf("no such file or directory: %s", av);
		free(temp);
		free(arg0);
		exit (1);
	}
}
