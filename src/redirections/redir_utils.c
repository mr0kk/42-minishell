/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:51:39 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 20:35:42 by ajurczyk         ###   ########.fr       */
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
