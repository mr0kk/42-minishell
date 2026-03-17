/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:21:24 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/17 15:21:26 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	creates new string with replaced variable name by its value
*/
char	*create_exp_str(char *old_s, char *var_n, char *var_val, size_t d_i)
{
	size_t	new_len;
	char	*new_s;

	new_len = ft_strlen(old_s) - 1 - ft_strlen(var_n) + ft_strlen(var_val);
	new_s = (char *)malloc((new_len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, old_s, d_i + 1);
	ft_strlcat(new_s, var_val, new_len + 1);
	ft_strlcat(new_s, old_s + d_i + 1 + ft_strlen(var_n), new_len + 1);
	return (new_s);
}

/*
	function takes token with $ in it and its index
	and returns new one with expaned variable
*/
char	*replace_var(char *s, size_t *d_i, char *envp[], t_data *data)
{
	char	*new_s;
	char	*var_n;
	char	*var_val;

	var_n = get_var_name(s, *d_i);
	if (!var_n)
		return (free_vars(var_n, NULL, NULL));
	if (ft_strncmp(var_n, "?", 2) == 0)
		var_val = ft_itoa(data->last_exit_code);
	else
	{
		var_val = find_var_value(var_n, envp);
		if (!var_val)
			return (free_vars(var_val, NULL, NULL));
	}
	new_s = create_exp_str(s, var_n, var_val, *d_i);
	if (!new_s)
		return (free_vars(var_n, var_val, NULL));
	*d_i += ft_strlen(var_val);
	free_vars(var_n, var_val, NULL);
	return (new_s);
}

/*
	function hadles replacing token 
	with expanded version of it
*/
bool	perform_expansion(t_token *curr, size_t *i, char **envp, t_data *data)
{
	char	*s;

	s = replace_var(curr->token, i, envp, data);
	if (!s)
	{
		error_message("Memory allocation error");
		return (1);
	}
	free(curr->token);
	curr->token = s;
	return (0);
}

/*
	function replacing envariamental variabes with its values
	and changing given tokens linked list
*/
bool	process_token(t_token *cur, char **envp, t_data *data)
{
	t_quote_state	state;
	size_t			i;

	i = 0;
	state = OUTSIDE;
	while (cur->token[i])
	{
		update_quote_state(cur->token[i], &state);
		if (cur->token[i] == 36 && (ft_isalnum(cur->token[i + 1])
				|| cur->token[i + 1] == '_' || cur->token[i + 1] == '?')
			&& state != IN_SINGLE)
		{
			if (perform_expansion(cur, &i, envp, data))
				return (1);
		}
		else
			i++;
	}
	return (quote_error(&state));
}

bool	expand_variables(t_token *head, char **envp, t_data *data)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (process_token(current, envp, data))
			return (1);
		current = current->next;
	}
	return (0);
}
