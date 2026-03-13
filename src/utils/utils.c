/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:51:48 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 19:27:41 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_separator(char c)
{
	return (c == ' ' || c == '\t');
}

/*
	helper function for freeing stings
*/
char	*free_vars(char	*a, char *b, char *c)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	return (NULL);
}
