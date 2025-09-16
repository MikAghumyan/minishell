#include "../../includes/minishell.h"


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
