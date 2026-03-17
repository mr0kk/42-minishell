#include "minishell.h"

static unsigned int	count_words(char const *s)
{
	int		count;
	int		i;
	char	q;

	count = 0;
	i = 0;
	q = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i])
			count++;
		while (s[i])
		{
			if (!q && (s[i] == '\'' || s[i] == '"'))
				q = s[i];
			else if (q == s[i])
				q = 0;
			else if (!q && (s[i] == ' ' || s[i] == '\t'))
				break ;
			i++;
		}
	}
	return (count);
}

static char	*extract_word(char const *s, unsigned int *index)
{
	unsigned int	start;
	char			q;

	q = 0;
	while (s[*index] == ' ' || s[*index] == '\t')
		(*index)++;
	start = *index;
	while (s[*index])
	{
		if (!q && (s[*index] == '\'' || s[*index] == '"'))
			q = s[*index];
		else if (q == s[*index])
			q = 0;
		else if (!q && (s[*index] == ' ' || s[*index] == '\t'))
			break ;
		(*index)++;
	}
	if (*index > start)
		return (ft_substr(s, start, *index - start));
	return (NULL);
}

char	**split_quotes(char const *s)
{
	char			**res;
	unsigned int	words;
	unsigned int	i;
	unsigned int	j;

	words = count_words(s);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < words)
	{
		res[i] = extract_word(s, &j);
		i++;
	}
	res[i] = NULL;
	return (res);
}
