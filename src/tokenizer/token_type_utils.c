#include "../../includes/minishell.h"

static e_token_type	get_redir_type(const char *input, size_t i)
{
	if (ft_strncmp(&input[i], ">>", 2) == 0)
		return (TOKEN_APPEND);
	if (ft_strncmp(&input[i], "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	if (input[i] == '<')
		return (TOKEN_REDIRECT_IN);
	if (input[i] == '>')
		return (TOKEN_REDIRECT_OUT);
	return (TOKEN_INVALID);
}

static e_token_type	get_operator_type(const char *input, size_t i)
{
	if (ft_strncmp(&input[i], "&&", 2) == 0)
		return (TOKEN_AND);
	if (ft_strncmp(&input[i], "||", 2) == 0)
		return (TOKEN_OR);
	if (input[i] == '|')
		return (TOKEN_PIPE);
	if (input[i] == '&' || input[i] == ';')
		return (TOKEN_INVALID);
	if (input[i] == '(')
		return (TOKEN_LPAREN);
	if (input[i] == ')')
		return (TOKEN_RPAREN);
	return (TOKEN_INVALID);
}

t_token	*add_redirect_token(t_token **tokens, t_shell *shell, size_t *i)
{
	e_token_type	type;
	char			*value;
	t_token			*res;
	size_t			start;

	if (!shell || !shell->input || !tokens || !i)
		return (NULL);
	type = get_redir_type(shell->input, *i);
	start = *i;
	if (type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		(*i) += 2;
	else
		(*i) += 1;
	while (shell->input[*i] && (shell->input[*i] == ' '
			|| shell->input[*i] == '\t'))
		(*i)++;
	if (!shell->input[*i] || token_is_operator(shell->input[*i]))
		return (add_token_slice(tokens, &shell->input[start], 2,
				TOKEN_INVALID));
	value = get_word_value(shell, i, &type);
	if (!value)
		return (NULL);
	res = add_token_slice(tokens, value, ft_strlen(value), type);
	return (free(value), res);
}

t_token	*add_operator_token(t_token **tokens, t_shell *shell, size_t *i)
{
	e_token_type	type;
	size_t			end;

	if (!shell || !shell->input || !tokens || !i)
		return (NULL);
	if (shell->input[*i] == '<' || shell->input[*i] == '>')
		return (add_redirect_token(tokens, shell, i));
	type = get_operator_type(shell->input, *i);
	if (type == TOKEN_AND || type == TOKEN_OR)
		end = 2;
	else
		end = 1;
	*i += end;
	return (add_token_slice(tokens, &shell->input[*i - end], end, type));
	return (NULL);
}
