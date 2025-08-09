#include "../../includes/minishell.h"

t_token	*add_operator_token(t_token **tokens, const char *value, size_t *i)
{
	if (!value || !*value)
		return (NULL);
	if (ft_strncmp(value, "&&", 2) == 0)
		return ((*i) += 2, add_token(tokens, value, TOKEN_AND));
	if (ft_strncmp(value, "||", 2) == 0)
		return ((*i) += 2, add_token(tokens, value, TOKEN_OR));
	if (ft_strncmp(value, "|", 1) == 0)
		return ((*i)++, add_token(tokens, value, TOKEN_PIPE));
	if (ft_strncmp(value, "<", 1) == 0)
		return ((*i)++, add_token(tokens, value, TOKEN_REDIRECT_IN));
	if (ft_strncmp(value, ">", 1) == 0)
		return ((*i)++, add_token(tokens, value, TOKEN_REDIRECT_OUT));
	if (ft_strncmp(value, ">>", 2) == 0)
		return ((*i) += 2, add_token(tokens, value, TOKEN_APPEND));
	if (ft_strncmp(value, "<<", 2) == 0)
		return ((*i) += 2, add_token(tokens, value, TOKEN_HEREDOC));
	if (ft_strncmp(value, "$", 1) == 0)
		return ((*i)++, add_token(tokens, value, TOKEN_ENV_VAR));
	if (ft_strncmp(value, "'", 1) == 0)
		return ((*i)++, add_token(tokens, value, TOKEN_QUOTE));
	if (ft_strncmp(value, "\"", 1) == 0)
		return ((*i)++, add_token(tokens, value, TOKEN_DQUOTE));
	return (NULL);
}

t_token	*tokenize_input(t_shell *shell)
{
	size_t	i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (shell->input[i])
	{
		if (shell->input[i] == ' ' || shell->input[i] == '\t')
			++i;
		else
		{
			if (is_operator(shell->input[i]))
			{
				add_operator_token(&tokens, &shell->input[i], &i);
			}
			else
			{
				add_token(&tokens, "<word>", TOKEN_WORD);
				++i;
			}
		}
	}
	print_tokens(tokens);
	return (tokens);
}
