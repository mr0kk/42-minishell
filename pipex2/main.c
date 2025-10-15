/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:56:41 by ajurczyk          #+#    #+#             */
/*   Updated: 2025/05/10 14:04:48 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **ep)
{
	int	pipe1[2];
	int	pid;

	check_ac_av(ac, av);
	if (pipe(pipe1) == -1)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
		do_write(pipe1, av, ep);
	else
		do_read(pipe1, av, ep);
	close(pipe1[0]);
	close(pipe1[1]);
	waitpid(pid, NULL, 0);
	return (0);
}
