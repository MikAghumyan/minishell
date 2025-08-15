#include "../../includes/minishell.h"

size_t	scan_word(const char *input, size_t start)
{
	size_t	end;

	end = start;
	while (input[end] && input[end] != ' ' && input[end] != '\t'
		&& !is_operator(input[end]))
		end++;
	return (end);
}

int	add_word_token(t_token **tokens, const char *input, size_t *i)
{
	size_t	word_end;
	size_t	word_start;

	if (!tokens || !input || !i)
		return (-1);
	word_start = *i;
	word_end = scan_word(input, *i);
	if (word_end == *i)
		return (-1);
	*i = word_end;
	return (add_token_slice(tokens, &input[word_start], word_end - word_start,
			TOKEN_WORD));
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
	if (ft_strncmp(&input[*i], ">>", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &input[*i - 2], 2,
				TOKEN_APPEND));
	if (ft_strncmp(&input[*i], "<<", 2) == 0)
		return ((*i) += 2, add_token_slice(tokens, &input[*i - 2], 2,
				TOKEN_HEREDOC));
	if (input[*i] == '|')
		return ((*i)++, add_token_slice(tokens, &input[*i - 1], 1, TOKEN_PIPE));
	if (input[*i] == '<')
		return ((*i)++, add_token_slice(tokens, &input[*i - 1], 1,
				TOKEN_REDIRECT_IN));
	if (input[*i] == '>')
		return ((*i)++, add_token_slice(tokens, &input[*i - 1], 1,
				TOKEN_REDIRECT_OUT));
	return (-1);
}