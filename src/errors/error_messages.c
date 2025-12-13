
#include "minishell.h"

bool	exit_syntax_error(char *s)
{
	printf("minishell: syntax error near unexpected token \'%s\'\n", s);
	return (1);
}

void	error_message(char *s)
{
	ft_printf("minishell: %s\n", s);
}

