#include "minishell.h"

/*
	function update quotes status 
	depending if any quote is open or not
*/
void	update_quote_state(char c, t_quote_state *state)
{
	if (*state == OUTSIDE)
	{
		if (c == '\'')
			*state = IN_SINGLE;
		else if (c == '\"')
			*state = IN_DOUBLE;
	}
	else if (*state == IN_SINGLE)
	{
		if (c == '\'')
            *state = OUTSIDE;
	}
	else if (*state == IN_DOUBLE)
	{
		if (c == '\"')
			*state = OUTSIDE;
	}
}

/*
	function separation variable name 
	and returns it as a string
*/
char	*get_var_name(char *s, size_t d_index)
{
	char	*var_name;
	size_t	i;
	size_t	len;

	len = 0;
	i = d_index + 1;
	while (s[i] && ft_isalpha(s[i]))
	{
		len++;
		i++;
	}
	var_name = (char *)malloc((len + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, s + d_index + 1, len + 1);
	return (var_name);
}