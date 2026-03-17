/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:51:39 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/17 15:21:41 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_redir_parts(t_token *head)
{
	t_token	*curr;
	char	**parts;
	char	*tmp;

	curr = head;
	parts = (char **)calloc(2, sizeof(char *));
	if (curr->type != FROM_FILE || curr->type != REPLACE
		|| curr->type != ADD_END || curr->type != HEREDOC)
	{
		tmp = parts[0];
		parts[0] = ft_strjoin(tmp, curr->token);
		tmp = parts[0];
		parts[0] = ft_strjoin(tmp, " ");
		curr = curr->next;
	}
	curr = curr->next;
	tmp = parts[1];
	parts[1] = ft_strjoin(tmp, curr->token);
	tmp = parts[1];
	parts[1] = ft_strjoin(tmp, " ");
	return (parts);
}

ssize_t	read_line(char *buffer, size_t size)
{
	size_t	i;
	char	c;
	ssize_t	r;

	i = 0;
	while (i < size - 1)
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r <= 0)
			return (r);
		if (c == '\n')
			break ;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	return (i);
}

void	put_ft_util(int fd, char *line)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_signal_pid = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

int	abort_heredoc(int stdin_backup, char *line)
{
	free(line);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	return (-1);
}
