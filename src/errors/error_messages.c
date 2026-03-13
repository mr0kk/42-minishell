/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:28 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 14:04:48 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exit_syntax_error(char *s)
{
	printf("minishell: syntax error near unexpected token \'%s\'\n", s);
	return (1);
}

void	error_message(char *s)
{
	ft_printf("minishell: %s\n", s);
}
