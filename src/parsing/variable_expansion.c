#include "minishell.h"

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

char	*replace_var(char *s, size_t d_index, char *envp[])
{
	char	*new_s;
	char	*var_name;
	char	*var_value;
	size_t	i;

	i = d_index;
	var_name = get_var_name(s, d_index);
	if (!var_name)
		return (NULL);
	var_value = find_var_value(var_name, envp);
	if (!var_value)
		return (NULL);
	new_s = create_exp_str(s, var_name, var_value, d_index);
	free(var_name);
	free(var_value);
	return (new_s);
}

void	expand_variables(t_token *head, char **envp)
{
	t_token	*current;
	char	*s;

	current = head;
	while (current)
	{
		while (is_dolar(current->token) >= 0)
		{
			s = replace_var(current->token, (size_t)(is_dolar(current->token)), envp);
			if (!s)
				exit_shell(); // do poprawy
			free(current->token);
			current->token = s;
		}
		current = current->next;
	}
}