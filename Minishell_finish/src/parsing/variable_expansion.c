#include "minishell.h"

/*
	interating throuht envp[] looking for given variable name
	when variable exist returns its string value 
	empty string otherwise
*/
char	*find_var_value(char *var_name, char *envp[])
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(var_name, envp[i], ft_strlen(var_name)))
			return (ft_strdup(envp[i] + ft_strlen(var_name) + 1));
		i++;
	}
	return (ft_strdup(""));
}

/*
	creates new string with replaced variable name by its value
*/
char	*create_exp_str(char *old_s, char *var_name, char *var_value, size_t d_index)
{
	size_t	i;
	size_t	val_i;
	size_t	new_len;
	char	*new_s;

	new_len = ft_strlen(old_s) - 1 - ft_strlen(var_name) + ft_strlen(var_value);
	new_s = (char *)malloc((new_len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	i = 0;
	while (old_s[i] && i < d_index)
		new_s[i++] = old_s[i];
	val_i = 0;
	while (var_value[val_i])
		new_s[i++] = var_value[val_i++];
	d_index = d_index + 1 + ft_strlen(var_name);
	while (old_s[d_index])
		new_s[i++] = old_s[d_index++];
	new_s[i] = '\0';
	return (new_s);
}


/*
	function takes token with $ in it and its index
	and returns new one with expaned variable
*/
char	*replace_var(char *s, size_t *d_index, char *envp[], t_data *data)
{
	char	*new_s;
	char	*var_name;
	char	*var_value;
	size_t	i;

	i = *d_index;
	var_name = get_var_name(s, *d_index);
	if (!var_name)
		return (free_vars(var_name, NULL, NULL));
	if (ft_strncmp(var_name, "?", 2) == 0)
		var_value = ft_itoa(data->last_exit_code);
	else
	{
		var_value = find_var_value(var_name, envp);
		if (!var_value)
			return (free_vars(var_value, NULL, NULL));
	}
	new_s = create_exp_str(s, var_name, var_value, *d_index);
	if (!new_s)
		return (free_vars(var_name, var_value, NULL));
	*d_index += ft_strlen(var_value);
	free_vars(var_name, var_value, NULL);
	return (new_s);
}

/*
	function hadles replacing token 
	with expanded version of it
*/
bool	perform_expansion(t_token *current, size_t *i, char **envp, t_data *data)
{
	char	*s;

	s = replace_var(current->token, i, envp, data);
	if (!s)
	{
		error_message("Memory allocation error");
		return (1);
	}
	free(current->token);
	current->token = s;
	return (0);
}

/*
	function replacing envariamental variabes with its values
	and changing given tokens linked list
*/
bool	expand_variables(t_token *head, char **envp, t_data *data)
{
	t_token	*current;
	t_quote_state state;
	size_t	i;

	current = head;
	while (current)
	{
		i = 0;
		state = OUTSIDE;
		while (current->token[i])
		{
			update_quote_state(current->token[i], &state);
			if (current->token[i] == 36 && (ft_isalnum(current->token[i + 1]) || current->token[i + 1] == '_' || current->token[i + 1] == '?') && state != IN_SINGLE)
			{
				if (perform_expansion(current, &i, envp, data))
					return (1);
			}
			else
				i++;
		}
		if (quote_error(&state))
			return (1);
		current = current->next;
	}
	return (0);
}
