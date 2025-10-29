#include "minishell.h"

void	ft_echo(t_token *head)
{
	t_token	*tmp;
	bool	nl;

	nl = 1;
	if (!head)
		return ;
	tmp = head->next;
	if (!ft_strncmp(tmp->token, "-n", 3))
	{
		nl = 0;
		tmp = head->next;
	}
	while (tmp)
    {
        printf("%s", tmp->token);
		if (tmp->next)
			printf(" ");
        tmp = tmp->next;
    }
	if (nl)
		printf("\n");
}