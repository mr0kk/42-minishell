#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

/*
	structures
*/
typedef struct s_data
{
	bool	interative;
	char	*user_input;
}	t_data;

typedef enum e_token_type
{
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	FILE_TOKEN,
	UNKNOWN
}	t_token_type;

typedef struct s_token
{
	size_t	token_len;
	char	*token;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;


void	exit_shell();
/*
	parsing
*/
int		input_valid(t_data *data, int argc, char **argv);
void	input_handler(t_data *data, char **envp);
void	define_tokens_type(t_token *head);
void	expand_variables(t_token *head, char **envp);

/*
	nodes handling
*/
t_token	*create_node(char *text);
void	add_node(t_token **head, char *text);
void	free_tokens(t_token **head);

/*
	commands
*/
void	ft_echo(t_token *head);

/*
	pipes
*/
void	pipes(char **cmds, char **ep);

/*
	errors
*/
bool	syntax_error(t_token *head);
bool	exit_syntax_error(char *s);

/*
	utilities functions
*/
void	print_tokens(t_token *head);
bool	is_separator(char c);
int		is_dolar(char *s);
void	check_for_pipe(t_token *head, char **envp);


#endif