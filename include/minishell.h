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
#include <signal.h>
#include <readline/history.h>

#define PATH 4020

extern int g_signal_pid;

/*
	structures
*/
typedef struct s_data
{
	bool	interative;
	char	*user_input;
	char	**envp;
	int		last_exit_code;
}	t_data;

typedef enum e_quote_state
{
	OUTSIDE,
	IN_SINGLE,
	IN_DOUBLE
}	t_quote_state;

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

/*
	parsing
*/
int		input_valid(t_data *data, int argc, char **argv);
void	input_handler(t_data *data, char **envp);
void	define_tokens_type(t_token *head);
bool	expand_variables(t_token *head, char **envp, t_data *data);
void	get_token_ready(t_token *head);
void	remove_quotes(t_token *head);
void	add_env(t_data *data, char **envp);

/*
	nodes handling
*/
t_token	*create_node(char *text);
void	add_node(t_token **head, char *text);
void	free_tokens(t_token **head);

/*
	commands
*/
void	cmd_cd(t_token *head);
void	cmd_echo(t_token *head);
void	cmd_env(t_data *data);
void	cmd_exit(t_token *head);
void 	cmd_export(t_token *head, t_data *data);
void 	cmd_pwd(t_token *head);
void	cmd_unset(t_token *head, t_data *data);
void	exec_cmd(char *av, char **envp);

/*
	execution
*/
int		start_execution(t_token *head, t_data *data);
void	init_signals(void);
void	defauld_signals_in_child(void);
void	ignore_signals_in_parent(void);

/*
	errors
*/
void	exit_shell(char *message);
bool	syntax_error(t_token *head);
bool	exit_syntax_error(char *s);
void	error_message(char *s);
bool	quote_error(t_quote_state *state);

/*
	utilities functions
*/
void	print_tokens(t_token *head);
bool	is_separator(char c);
void	check_for_pipe(t_token *head, char **envp);
void	update_quote_state(char c, t_quote_state *state);
char	*free_vars(char	*a, char *b, char *c);
char	*get_var_name(char *s, size_t d_index);
void	update_quote_state(char c, t_quote_state *state);
void	check_for_buildins(t_token *head, t_data *data);

#endif