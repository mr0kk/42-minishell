/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:47:29 by rmrok             #+#    #+#             */
/*   Updated: 2025/10/22 21:55:14 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_table(char **tab)
{
	int	i;

	i = 0; 
}

void	parser(t_data *data)
{
	char	**instructions;

	printf("%s\n", data->user_input);
	instructions = ft_split(data->user_input, ' ');
	
}