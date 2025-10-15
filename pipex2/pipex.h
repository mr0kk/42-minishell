/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:03:00 by ajurczyk          #+#    #+#             */
/*   Updated: 2025/05/10 14:05:56 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <fcntl.h>

char	*get_ep_path(char **ep, char *cmd);
char	*return_path(char **env_paths, char *cmd);
int		open_file(char *file, int in_or_out);
void	do_read(int *pipe1, char **av, char **envp);
void	do_write(int *pipe1, char **av, char **envp);
void	wrong_command(char *s);
void	wrong_file_av1(char *s);
void	wrong_file_av2(char *s);
void	check_ac_av(int ac, char **av);
int		check_command(char **ep, char *cmd);

#endif
