/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:50:22 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 14:05:00 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	function checks if quotes are closed 
	and return errro if not
*/
bool	quote_error(t_quote_state *state)
{
	if (*state == OUTSIDE)
		return (0);
	else if (*state == IN_DOUBLE)
		error_message("unexpected EOF while looking for matching \'\"\'");
	else if (*state == IN_SINGLE)
		error_message("unexpected EOF while looking for matching \'\'\'");
	return (1);
}

void	exit_shell(char *message)
{
	// printf("minishell[TEST]: %s\n", message);
	perror(message);
	// free_all(data);
	exit(1);
}
