
#include "../../includes/minishell.h"

static char	*add_word_slice(t_token **tokens, t_shell *shell, size_t *i,
		t_tokres *result_code)
{
	size_t	word_end;
	size_t	word_start;
	char	*word_slice;
	char	*expanded;

	if (!tokens || !shell || !i)
		return (*result_code = TOKEN_RES_ERROR, NULL);
	word_start = *i;
	word_end = scan_word(shell->input, *i, ' ');
	if (word_end == *i)
		return (*result_code = TOKEN_RES_INVALID, NULL);
	*i = word_end;
	word_slice = ft_substr(shell->input, word_start, word_end - word_start);
	if (!word_slice)
		return (*result_code = TOKEN_RES_MEMORY_ERROR, NULL);
	expanded = expand_token_value(shell, word_slice);
	free(word_slice);
	if (!expanded)
		return (*result_code = TOKEN_RES_MEMORY_ERROR, NULL);
	return (expanded);
}

char	*add_quote_slice(t_token **tokens, t_shell *shell, size_t *i,
		t_tokres *result_code)
{
	size_t	start;
	char	*word_slice;
	char	*expanded;

	if (!tokens || !shell || !i)
		return (*result_code = TOKEN_RES_ERROR, NULL);
	start = ++(*i);
	if (shell->input[start - 1] == '\'')
		*i = scan_word(shell->input, *i, '\'');
	if (shell->input[start - 1] == '\"')
		*i = scan_word(shell->input, *i, '\"');
	if (!shell->input[*i])
		return (*result_code = TOKEN_RES_SYNTAX_ERROR, NULL);
	word_slice = ft_substr(shell->input, start, *i - start);
	(*i)++;
	if (shell->input[start - 1] == '\"')
	{
		expanded = expand_token_value(shell, word_slice);
		free(word_slice);
		if (!expanded)
			return (*result_code = TOKEN_RES_MEMORY_ERROR, NULL);
		word_slice = expanded;
	}
	return (word_slice);
}

t_tokres	process_token_part(t_shell *shell, size_t *i, t_token **tokens,
		char **value)
{
	char		*value_slice;
	char		*tmp;
	t_tokres	result_code;

	result_code = TOKEN_RES_SUCCESS;
	value_slice = NULL;
	if (shell->input[*i] == '\"' || shell->input[*i] == '\'')
		value_slice = add_quote_slice(tokens, shell, i, &result_code);
	else
		value_slice = add_word_slice(tokens, shell, i, &result_code);
	if (result_code == TOKEN_RES_SYNTAX_ERROR)
		printf("minishell: syntax error: unmatched quote\n");
	if (!value_slice)
		return (result_code);
	if (!*value)
		*value = ft_strdup("");
	tmp = *value;
	*value = ft_strjoin(*value, value_slice);
	free(tmp);
	free(value_slice);
	if (!*value)
		return (TOKEN_RES_MEMORY_ERROR);
	return (TOKEN_RES_SUCCESS);
}

t_tokres	process_quote_or_word(t_shell *shell, size_t *i, t_token **tokens)
{
	t_token		*token;
	char		*value;
	t_tokres	result_code;

	token = NULL;
	value = NULL;
	while (shell->input[*i] && shell->input[*i] != ' '
		&& !token_is_operator(shell->input[*i]))
	{
		result_code = process_token_part(shell, i, tokens, &value);
		if (result_code != TOKEN_RES_SUCCESS)
		{
			free(value);
			return (result_code);
		}
	}
	if (value)
	{
		token = add_token_slice(tokens, value, ft_strlen(value), TOKEN_WORD);
		free(value);
		if (!token)
			return (TOKEN_RES_MEMORY_ERROR);
	}
	return (TOKEN_RES_SUCCESS);
}
