/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:37:56 by ajurczyk          #+#    #+#             */
/*   Updated: 2025/05/10 15:58:31 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_ac_av(int ac, char **av)
{
	if (ac != 5)
		exit(1);
	if (ft_strlen(av[2]) == 0)
		exit(1);
	if (ft_strlen(av[3]) == 0)
		exit(1);
	if (open(av[1], O_RDWR) < 0)
		wrong_file_av1(av[1]);
	if (open(av[4], O_RDWR) < 0)
		wrong_file_av2(av[4]);
}

int	check_command(char **ep, char *cmd)
{
	char	**env_paths;

	while (*ep)
	{
		if (ft_strncmp(*ep, "PATH", 4) == 0)
			break ;
		ep++;
	}
	env_paths = ft_split(*ep + 5, ':');
	if (return_path(env_paths, cmd) == 0)
	{
		ft_free(env_paths);
		return (1);
	}
	else
		return (0);
}
