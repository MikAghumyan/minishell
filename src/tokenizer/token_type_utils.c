#include "../../includes/minishell.h"

size_t	scan_word(const char *input, size_t start, const char end_char)
{
	size_t	end;

	end = start;
	if (end_char != ' ')
	{
		while (input[end] && input[end] != end_char)
			end++;
	}
	else
	{
		while (input[end] && input[end] != ' ' && input[end] != '\t'
			&& input[end] != '\'' && input[end] != '\"'
			&& !token_is_operator(input[end]))
			end++;
	}
	return (end);
}

int	add_word_token(t_token **tokens, const char *input, size_t *i)
{
	size_t	word_end;
	size_t	word_start;

	if (!tokens || !input || !i)
		return (-1);
	word_start = *i;
	word_end = scan_word(input, *i, ' ');
	if (word_end == *i)
		return (-1);
	*i = word_end;
	return (add_token_slice(tokens, &input[word_start], word_end - word_start,
			TOKEN_WORD));
}

int	add_redirect_token(t_token **tokens, const char *input, size_t *i)
{
	if (!input || !input[*i] || !tokens || !i)
		return (-1);
	if (ft_strncmp(&input[*i], ">>", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &input[*i - 2], 2,
				TOKEN_APPEND));
	if (ft_strncmp(&input[*i], "<<", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &input[*i - 2], 2,
				TOKEN_HEREDOC));
	if (input[*i] == '<')
		return ((*i)++, add_token_slice(tokens, &input[*i - 1], 1,
				TOKEN_REDIRECT_IN));
	if (input[*i] == '>')
		return ((*i)++, add_token_slice(tokens, &input[*i - 1], 1,
				TOKEN_REDIRECT_OUT));
	return (-1);
}

int	add_operator_token(t_token **tokens, const char *input, size_t *i)
{
	if (!input || !input[*i] || !tokens || !i)
		return (-1);
	if (ft_strncmp(&input[*i], "&&", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &input[*i - 2], 2,
				TOKEN_AND));
	if (ft_strncmp(&input[*i], "||", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &input[*i - 2], 2,
				TOKEN_OR));
	if (input[*i] == '&' || input[*i] == ';')
		return ((*i)++, add_token_slice(tokens, &input[*i - 1], 1,
				TOKEN_INVALID));
	if (input[*i] == '|')
		return ((*i)++, add_token_slice(tokens, &input[*i - 1], 1, TOKEN_PIPE));
	if (input[*i] == '<' || input[*i] == '>')
		return (add_redirect_token(tokens, input, i));
	if (input[*i] == '(')
		return ((*i)++, add_token_slice(tokens, &input[*i - 1], 1,
				TOKEN_LPAREN));
	if (input[*i] == ')')
		return ((*i)++, add_token_slice(tokens, &input[*i - 1], 1,
				TOKEN_RPAREN));
	return (-1);
}

int	add_quote_token(t_token **tokens, const char *input, size_t *i)
{
	size_t	start;

	if (!tokens || !input || !i)
		return (-1);
	start = ++(*i);
	if (input[*i - 1] == '\'')
	{
		*i = scan_word(input, *i, '\'');
		if (!input[*i])
			return (-1);
		return ((*i)++, add_token_slice(tokens, &input[start], *i - start - 1,
				TOKEN_QUOTE));
	}
	if (input[*i - 1] == '\"')
	{
		*i = scan_word(input, *i, '\"');
		if (!input[*i])
			return (-1);
		return ((*i)++, add_token_slice(tokens, &input[start], *i - start - 1,
				TOKEN_DQUOTE));
	}
	return (-1);
}
