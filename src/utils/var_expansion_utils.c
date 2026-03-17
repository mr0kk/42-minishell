/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:21:59 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/17 15:22:01 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	i = d_index + 1;
	if (s[i] == '?')
		return (ft_strdup("?"));
	len = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
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

/*
	interating throuht envp[] looking for given variable name
	when variable exist returns its string value 
	empty string otherwise
*/
char	*find_var_value(char *var_name, char *envp[])
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (!ft_strncmp(var_name, envp[i], len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}
