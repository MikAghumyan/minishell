
#include "../../includes/minishell.h"

static char	*add_word_slice(t_token **tokens, t_shell *shell, size_t *i)
{
	size_t	word_end;
	size_t	word_start;
	char	*word_slice;
	char	*expanded;

	if (!tokens || !shell || !i)
		return (NULL);
	word_start = *i;
	word_end = scan_word(shell->input, *i, ' ');
	if (word_end == *i)
		return (NULL);
	*i = word_end;
	word_slice = ft_substr(shell->input, word_start, word_end - word_start);
	if (!word_slice)
		return (NULL);
	expanded = expand_token_value(shell, word_slice);
	free(word_slice);
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*add_quote_slice(t_token **tokens, t_shell *shell, size_t *i)
{
	size_t	start;
	char	*word_slice;
	char	*expanded;

	if (!tokens || !shell || !i)
		return (NULL);
	start = ++(*i);
	if (shell->input[start - 1] == '\'')
		*i = scan_word(shell->input, *i, '\'');
	if (shell->input[start - 1] == '\"')
		*i = scan_word(shell->input, *i, '\"');
	if (!shell->input[*i])
		return (printf("minishell: syntax error\n"), NULL);
	word_slice = ft_substr(shell->input, start, *i - start);
	(*i)++;
	if (shell->input[start - 1] == '\"')
	{
		expanded = expand_token_value(shell, word_slice);
		free(word_slice);
		if (!expanded)
			return (NULL);
		word_slice = expanded;
	}
	return (word_slice);
}

static int	process_token_part(t_shell *shell, size_t *i, t_token **tokens,
		char **value)
{
	char	*value_slice;
	char	*tmp;

	if (shell->input[*i] == '\"' || shell->input[*i] == '\'')
		value_slice = add_quote_slice(tokens, shell, i);
	else
		value_slice = add_word_slice(tokens, shell, i);
	if (!value_slice)
	{
		return (-1);
	}
	if (!*value)
		*value = ft_strdup("");
	tmp = *value;
	*value = ft_strjoin(*value, value_slice);
	free(tmp);
	free(value_slice);
	if (!*value)
		return (-1);
	return (0);
}

int	process_quote_or_word(t_shell *shell, size_t *i, t_token **tokens)
{
	t_token *token;
	char *value;

	token = NULL;
	value = NULL;
	while (shell->input[*i] && shell->input[*i] != ' '
		&& !token_is_operator(shell->input[*i]))
	{
		if (process_token_part(shell, i, tokens, &value) == -1)
		{
			free(value);
			return (-1);
		}
	}
	if (value)
	{
		token = add_token_slice(tokens, value, ft_strlen(value), TOKEN_WORD);
		free(value);
		if (!token)
			return (-1);
	}
	return (0);
}