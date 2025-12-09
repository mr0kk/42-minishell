#include "minishell.h"


/*
	function iterates throught separators to skip them
*/
void	skip_separators(char *input, int *index)
{
	while (input[*index] && is_separator(input[*index]))
		(*index)++;
}

/*
	function separates first met token from given string
	and updates index variable for next index after token
	return token string
*/
char	*read_token(char *input, int *index)
{
	int		start;
	char	*res_token;
	char	quote_type;

	skip_separators(input, index);
	if (!input[*index])
        return (NULL);
	start = *index;
	quote_type = 0;
	while (input[*index])
	{
		if (input[*index] == '"' || input[*index] == '\'')
		{
			if (quote_type == 0)
				quote_type = input[*index];
			else if (quote_type == input[*index])
				quote_type = 0;
		}
		if (quote_type == 0 && is_separator(input[*index]))
			break ;
		(*index)++;
	}
	if (*index - start == 0)
		return (NULL);
	return (ft_substr(input, start, *index - start));
}
/*
	function takes input string and separetes it 
	creating tokens
	returns head element of linked list
*/
t_token *read_tokens(char *input)
{
	char	*token;
	t_token	*head;
	int		i;

	i = 0;
	head = NULL;
	while (input[i] || (i == 0 && !head))
	{
		token = read_token(input, &i);
		if (!token)
			break ;
		add_node(&head, token);
		free(token);
	}
	return (head);
}

void	input_handler(t_data *data, char **envp)
{
	t_token *head;
	
	head = read_tokens(data->user_input);
	define_tokens_type(head);
	
	if (syntax_error(head))
	{
		free_tokens(&head);
		return ;
	}
	expand_variables(head, envp);
	print_tokens(head);
	// check_for_pipe(head, envp);
	// if (!ft_strncmp(head->token, "echo", 5))
	// 	ft_echo(head);
	
	free_tokens(&head);
}
