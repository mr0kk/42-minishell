/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:21:53 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/17 15:21:55 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	free_all(t_data *data)
{
	free_env(data);
	free_tokens(&(data->head));
}

void	free_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
	data->envp = NULL;
}

void	free_2arrays_and_str(char **arr1, char **arr2, char *str)
{
	if (arr1)
		free_string_array(arr1);
	if (arr2)
		free_string_array(arr2);
	if (str)
		free(str);
}
