
#include "minishell.h"

char	*handle_nofile(char *path)
{
	char	*tmp;
	char	*err_msg;

	tmp = ft_strjoin("minishell: ", path);
	err_msg = ft_strjoin(tmp, ": No such file or directory\n");
	ft_putstr_fd(err_msg, 2);
	free(tmp);
	free(err_msg);
	free(path);
	return (NULL);
}

char	**prepare_args(char *av)
{
	char	**args;
	char	**clean_args;

	if (!av || !av[0])
		return (NULL);
	args = split_quotes(av);
	if (!*args)
		exit_shell("Memory allocation error");
	if (!(*args)[0])
	{
		free_string_array(args);
		return (NULL);
	}
	clean_args = handle_redirections(args);
	if (!clean_args || !clean_args[0])
	{
		free_2arrays_and_str(args, clean_args, NULL);
		return (NULL);
	}
	free_string_array(args);
	return (clean_args);
}

t_token	*argv_to_token_list(char **argv)
{
	t_token	*head;
	t_token	*curr;
	int		i;

	head = NULL;
	i = 0;
	if (!argv || !argv[0])
		return (NULL);
	while (argv[i])
		add_node(&head, argv[i++]);
	if (head)
	{
		head->type = CMD;
		curr = head->next;
		while (curr)
		{
			curr->type = ARG;
			curr = curr->next;
		}
	}
	return (head);
}

bool	is_redir(t_token_type type)
{
	return (type == FROM_FILE || type == REPLACE
		|| type == ADD_END || type == HEREDOC);
}

int	count_clean_args(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], ">>", 3) || !ft_strncmp(args[i], ">", 2)
			|| !ft_strncmp(args[i], "<", 2))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}
