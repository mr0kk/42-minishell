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

#define PATH 4096

/*
	structures
*/
typedef struct s_data
{
	bool	interative;
	char	*user_input;
	char	**envp;
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

/*
	execution
*/
void	start_execution(t_token *head, t_data *data);
void exec_cmd_withoutpipe(t_token *head, char *av, char **envp);
void	exec_cmd_absolutepath_withoutpipe(char *av, char **envp);
void	exec_cmd_absolutepath(char *av, char **envp);

/*
	execution utils
*/
char	*return_path(char **env_paths, char *cmd);
char	*get_path(char **ep, char *cmd);
int		check_command(char **ep, char *cmd);
int		check_for_pipes(t_token *head);
void	check_for_buildins(t_token *head, t_data *data);
char	**get_cmds(t_token *head, int numofcmds);

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


#endif