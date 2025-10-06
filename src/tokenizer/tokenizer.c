#include "../../includes/minishell.h"

t_tokres	process_single_char(t_shell *shell, size_t *i, t_token **tokens)
{
	t_tokres	result;

	result = TOKEN_RES_SUCCESS;
	if (shell->input[*i] == ' ' || shell->input[*i] == '\t')
		(*i)++;
	else if (!token_is_operator(shell->input[*i]))
	{
		result = add_word_token(shell, i, tokens);
	}
	else if (token_is_operator(shell->input[*i]))
	{
		if (!add_operator_token(tokens, shell, i))
			result = TOKEN_RES_MEMORY_ERROR;
		else if ((*tokens)->type == TOKEN_INVALID)
			result = TOKEN_RES_INVALID;
	}
	if (result == TOKEN_RES_MEMORY_ERROR)
		ft_putstr_fd("minishell: memory allocation failed\n", 2);
	return (result);
}

t_token	*tokenize_input(t_shell *shell)
{
	size_t		i;
	t_token		*tokens;
	t_tokres	res_;

	if (!shell || !shell->input)
		return (NULL);
	i = 0;
	tokens = NULL;
	while (shell->input[i])
	{
		res_ = process_single_char(shell, &i, &tokens);
		if (res_ != TOKEN_RES_SUCCESS)
		{
			if (res_ < TOKEN_RES_SUCCESS)
				handle_exit(shell);
			free_tokens(tokens);
			return (NULL);
		}
	}
	if (!analyze_tokens(tokens))
		return (free_tokens(tokens), NULL);
	print_tokens(tokens);
	return (tokens);
}
