#include "../../includes/minishell.h"

t_token	*add_operator_token(t_token **tokens, const char *input, size_t *i)
{
	if (!input || !input[*i])
		return (NULL);
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
	return (NULL);
}

size_t	scan_word(const char *input, size_t start)
{
	size_t	end;

	end = start;
	while (input[end] && input[end] != ' ' && input[end] != '\t'
		&& !is_operator(input[end]))
		end++;
	return (end);
}

t_token	*tokenize_input(t_shell *shell)
{
	size_t	i;
	size_t	word_end;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (shell->input[i])
	{
		if (shell->input[i] == ' ' || shell->input[i] == '\t')
			++i;
		else if (is_operator(shell->input[i]))
		{
			add_operator_token(&tokens, shell->input, &i);
		}
		else
		{
			word_end = scan_word(shell->input, i);
			add_token_slice(&tokens, &shell->input[i], word_end - i,
				TOKEN_WORD);
			i = word_end;
		}
	}
	print_tokens(tokens);
	return (tokens);
}
