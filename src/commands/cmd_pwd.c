#include "minishell.h"

void cmd_pwd(t_token *head)
{
	char	buff[PATH];
	char	*cwd;

	cwd = getcwd(buff, PATH);
	ft_putendl_fd(cwd, STDOUT_FILENO);
}