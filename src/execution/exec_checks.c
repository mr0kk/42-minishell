/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:04:40 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/18 16:54:31 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_redir_fd(t_token *curr)
{
	int	fd;

	if (curr->type == REPLACE || curr->type == ADD_END)
		return (replace_add_setup(curr, &fd));
	else if (curr->type == FROM_FILE)
	{
		fd = open(curr->next->token, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(curr->next->token);
			return (1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("minishell: dup2"), 1);
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
		return (cmd_exit(head, data));
	return (0);
}

void	check_for_buildins(t_token *head, t_data *data)
{
	int	stdout_backup;
	int	stdin_backup;
	int	exit_code;

	if (is_builtin(head))
	{
		remove_quotes_from_tokens(head);
		stdout_backup = dup(STDOUT_FILENO);
		stdin_backup = dup(STDIN_FILENO);
		if (apply_redirections(head) != 0)
		{
			dup2_and_close(stdin_backup, stdout_backup);
			return ;
		}
		exit_code = run_correct_cmd(head, data);
		data->last_exit_code = exit_code;
		dup2_and_close(stdin_backup, stdout_backup);
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
