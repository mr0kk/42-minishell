#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <readline/readline.h>

/*
	structures
*/
typedef struct s_data
{
	bool	interative;
	char	*user_input;
}	t_data;

typedef struct s_token
{
	size_t	token_len;
	char	*token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/*
	functions
*/
int	input_valid(t_data *data, int argc, char **argv);
void	input_handler(t_data *data);
char	**ft_strtok(char *str);

/*
	commands
*/
void	ft_echo(char **tab);

/*
	utilities functions
*/
void	print_tokens(char **instructions);

#endif