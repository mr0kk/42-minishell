#include "minishell.h"

void	cmd_cd(t_token *head)
{
	t_token *tmp;
	char	*path;

	if (!head)
		return ;
	tmp = head->next;
	chdir(tmp->token);
}