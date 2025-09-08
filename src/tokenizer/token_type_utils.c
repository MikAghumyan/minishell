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

t_token	*add_word_token(t_token **tokens, t_shell *shell, size_t *i)
{
	size_t	word_end;
	size_t	word_start;

	if (!tokens || !shell || !i)
		return (NULL);
	word_start = *i;
	word_end = scan_word(shell->input, *i, ' ');
	if (word_end == *i)
		return (NULL);
	*i = word_end;
	return (add_token_slice(tokens, &shell->input[word_start], word_end
			- word_start, TOKEN_WORD));
}

t_token	*add_redirect_token(t_token **tokens, t_shell *shell, size_t *i)
{
	if (!shell || !shell->input || !tokens || !i)
		return (NULL);
	if (ft_strncmp(&shell->input[*i], ">>", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &shell->input[*i - 2], 2,
				TOKEN_APPEND));
	if (ft_strncmp(&shell->input[*i], "<<", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &shell->input[*i - 2], 2,
				TOKEN_HEREDOC));
	if (shell->input[*i] == '<')
		return ((*i)++, add_token_slice(tokens, &shell->input[*i - 1], 1,
				TOKEN_REDIRECT_IN));
	if (shell->input[*i] == '>')
		return ((*i)++, add_token_slice(tokens, &shell->input[*i - 1], 1,
				TOKEN_REDIRECT_OUT));
	return (NULL);
}

t_token	*add_operator_token(t_token **tokens, t_shell *shell, size_t *i)
{
	if (!shell || !shell->input || !tokens || !i)
		return (NULL);
	if (ft_strncmp(&shell->input[*i], "&&", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &shell->input[*i - 2], 2,
				TOKEN_AND));
	if (ft_strncmp(&shell->input[*i], "||", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &shell->input[*i - 2], 2,
				TOKEN_OR));
	if (shell->input[*i] == '&' || shell->input[*i] == ';')
		return ((*i)++, add_token_slice(tokens, &shell->input[*i - 1], 1,
				TOKEN_INVALID));
	if (shell->input[*i] == '|')
		return ((*i)++, add_token_slice(tokens, &shell->input[*i - 1], 1,
				TOKEN_PIPE));
	if (shell->input[*i] == '<' || shell->input[*i] == '>')
		return (add_redirect_token(tokens, shell, i));
	if (shell->input[*i] == '(')
		return ((*i)++, add_token_slice(tokens, &shell->input[*i - 1], 1,
				TOKEN_LPAREN));
	if (shell->input[*i] == ')')
		return ((*i)++, add_token_slice(tokens, &shell->input[*i - 1], 1,
				TOKEN_RPAREN));
	return (NULL);
}

t_token	*add_quote_token(t_token **tokens, t_shell *shell, size_t *i)
{
	size_t	start;

	if (!tokens || !shell || !i)
		return (NULL);
	start = ++(*i);
	if (shell->input[*i - 1] == '\'')
	{
		*i = scan_word(shell->input, *i, '\'');
		if (!shell->input[*i])
			return (NULL);
		return ((*i)++, add_token_slice(tokens, &shell->input[start], *i - start
				- 1, TOKEN_WORD));
	}
	if (shell->input[*i - 1] == '\"')
	{
		*i = scan_word(shell->input, *i, '\"');
		if (!shell->input[*i])
			return (NULL);
		return ((*i)++, add_token_slice(tokens, &shell->input[start], *i - start
				- 1, TOKEN_WORD));
	}
	return (NULL);
}
