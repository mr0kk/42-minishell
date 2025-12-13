#include "minishell.h"

/*
	function checks if quotes are closed 
	and return errro if not
*/
bool	quote_error(t_quote_state *state)
{
	if (*state == OUTSIDE)
		return (0);
	else if (*state == IN_DOUBLE)
		error_message("unexpected EOF while looking for matching \'\"\'");
	else if (*state == IN_SINGLE)
		error_message("unexpected EOF while looking for matching \'\'\'");
	return (1);
}

void	exit_shell(char *message)
{
	printf("minishell: %s\n", message);
	exit(1);
}