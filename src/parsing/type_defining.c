#include "minishell.h"


void	classify_token(t_token *token)
{
	if (!ft_strncmp(token->token, "|", 2))
		token->type = PIPE;
	else if (!ft_strncmp(token->token, "<", 2) || !ft_strncmp(token->token, "<<", 3))
		token->type = REDIR_IN;
	else if (!ft_strncmp(token->token, ">", 2) || !ft_strncmp(token->token, ">>", 3))
		token->type = REDIR_OUT;
	else if (token->prev && (token->prev->type == REDIR_IN || token->prev->type == REDIR_OUT))
		token->type = FILE_TOKEN;
	else if (token->prev == NULL || token->prev->type == PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}


void	define_tokens_type(t_token *head)
{
	t_token	*tmp;

	tmp = head;

	while (tmp)
    {
        classify_token(tmp);
        tmp = tmp->next;
    }
}