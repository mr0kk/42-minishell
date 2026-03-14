/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:52:58 by ajurczyk          #+#    #+#             */
/*   Updated: 2026/03/07 20:35:58 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <readline/history.h>

# define PATH 4020

extern int	g_signal_pid;

/*
	structures
*/
typedef struct s_data
{
	bool	interative;
	char	*user_input;
	char	**envp;
	int		last_exit_code;
	struct s_token *head;
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
	REPLACE,
	FROM_FILE,
	HEREDOC,
	ADD_END,
	UNKNOWN
}	t_token_type;

typedef struct s_token
{
	size_t			token_len;
	char			*token;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;

}	t_token;

typedef struct s_exec
{
	char	**cmds;
	char	**envp;
	int		numofcmd;
	int		numofpipes;
}	t_exec;

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
void	free_all(t_data *data);

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
void	cmd_export(t_token *head, t_data *data);
void	cmd_pwd(t_token *head);
void	cmd_unset(t_token *head, t_data *data);
int		exec_cmd(char *av, char **envp, t_data *data);

/*
	execution
*/
int		check_for_type(t_token *current, t_token *head, t_data *data);
int		check_for_pipes(t_token *head);
void	check_for_buildins(t_token *head, t_data *data);
int		check_command(char **ep, char *cmd);
char	*return_path(char **env_paths, char *cmd);
char	*get_path(char **ep, char *cmd);
char	**get_cmds(t_token *head, int numofcmds);
void	check(char **envp, char *args);
char	*check_absolute_path(char *av, char **envp);
void	exec_cmd_withoutpipe(t_token *head, char *av, char **envp);
void	exec_cmd_absolutepath_withoutpipe(char *av, char **envp);
void	create_pipes(int (*fd)[2], int n);
void	child_process(int i, int (*fd)[2], t_exec *exec, t_data *data);
void	exec_pipes(char **cmds, t_data *data, int numofcmd);
void	start_pipes(t_token *head, t_data *data, int numofpipes);
void	start_execution(t_token *head, t_data *data);
void	ignore_signals_in_parent(void);
void	default_signals_in_child(void);
void	handle_signals(int sig);
void	init_signals(void);
char	**handle_redirections(char **args);

/*
	redirections
*/
int		redir_add_replace(char **args, int i);
int		redir_from_file(char **args, int i);
void	redir_heredoc(t_token *head, t_data *data);
char	**get_redir_parts(t_token *head);
ssize_t	read_line(char *buffer, size_t size);
int		ft_strcmp(const char *s1, const char *s2);

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
char	*find_var_value(char *var_name, char *envp[]);
void    free_string_array(char **arr);

#endif