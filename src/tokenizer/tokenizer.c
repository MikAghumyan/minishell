#include "../../includes/minishell.h"

t_tokres	process_single_char(t_shell *shell, size_t *i, t_token **tokens)
{
	t_tokres	result;

	if (shell->input[*i] == ' ' || shell->input[*i] == '\t')
		(*i)++;
	else if (!token_is_operator(shell->input[*i]))
	{
		result = process_quote_or_word(shell, i, tokens);
		if (result < TOKEN_RES_SUCCESS)
			return (result);
	}
	else if (token_is_operator(shell->input[*i]))
	{
		if (!add_operator_token(tokens, shell, i))
			return (TOKEN_RES_MEMORY_ERROR);
	}
	return (TOKEN_RES_SUCCESS);
}

t_token	*tokenize_input(t_shell *shell)
{
	size_t	i;
	t_token	*tokens;

	if (!shell || !shell->input)
		return (NULL);
	i = 0;
	tokens = NULL;
	while (shell->input[i])
	{
		if (process_single_char(shell, &i, &tokens) == -1)
		{
			// TODO HANDLE ERROR CODES
			free_tokens(tokens);
			return (NULL);
		}
	}
	if (!analyze_tokens(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	print_tokens(tokens);
	return (tokens);
}
