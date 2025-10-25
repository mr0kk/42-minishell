#include "minishell.h"

void	ft_echo(char **tab)
{
	int		i;
	bool	nl;

	nl = 1;
	if (!ft_strncmp(tab[0], "-n", 3))
	{
		i++;
		nl = 0;
	}
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
		if (tab[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
}