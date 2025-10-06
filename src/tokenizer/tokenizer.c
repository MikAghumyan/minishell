#include "../../includes/minishell.h"

t_token	*process_single_char(t_shell *shell, size_t *i, t_token **tokens)
{
	t_token	*token;

	token = NULL;
	if (shell->input[*i] == ' ' || shell->input[*i] == '\t')
		(*i)++;
	else if (!token_is_operator(shell->input[*i]))
	{
		token = add_word_token(shell, i, tokens);
	}
	else if (token_is_operator(shell->input[*i]))
	{
		token = add_operator_token(tokens, shell, i);
	}
	return (token);
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
		process_single_char(shell, &i, &tokens);
		if (!tokens)
		{
			perror("minishell: system error");
			handle_exit(shell);
		}
	}
	// printf("\n=== TOKENS ===\n");
	// print_tokens(tokens);
	// printf("==============\n");
	return (tokens);
}
