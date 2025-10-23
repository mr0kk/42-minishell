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
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**tokenization(char *input)
{
	char	**instructions;
	char	*holder;
	int		i;

	instructions = ft_split(input, ' ');
	i = 0;
	while (instructions[i])
	{
		holder = ft_strtrim(instructions[i], " \t");
		free(instructions[i]);
		instructions[i] = holder;
		i++;
	}
	return (instructions);
}

void	input_handler(t_data *data)
{
	char	**instructions;

	instructions = tokenization(data->user_input);
	int i = 0;
	while (instructions[i])
	{
		printf("%s\n", instructions[i]);
		i++;
	}
	free_table(instructions);
}