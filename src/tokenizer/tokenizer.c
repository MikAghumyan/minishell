#include "../../includes/minishell.h"

static int	process_quote_or_word(t_shell *shell, size_t *i, t_token **tokens)
{
	t_token	*token;

	token = NULL;
	if (shell->input[*i] == '\"')
	{
		token = add_quote_token(tokens, shell, i);
		if (!token)
			return (-1);
		if (!expand_token(shell, token))
			return (-1);
	}
	else if (shell->input[*i] == '\'')
	{
		if (!add_quote_token(tokens, shell, i))
			return (-1);
	}
	else
	{
		token = add_word_token(tokens, shell, i);
		if (!token)
			return (-1);
		if (!expand_token(shell, token))
			return (-1);
	}
	return (0);
}

static int	process_single_char(t_shell *shell, size_t *i, t_token **tokens)
{
	if (shell->input[*i] == ' ' || shell->input[*i] == '\t')
		(*i)++;
	else if (shell->input[*i] == '\"' || shell->input[*i] == '\''
		|| !token_is_operator(shell->input[*i]))
	{
		if (process_quote_or_word(shell, i, tokens) == -1)
			return (-1);
	}
	else if (token_is_operator(shell->input[*i]))
	{
		if (!add_operator_token(tokens, shell, i))
			return (-1);
	}
	return (0);
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
			shell->exit_status = 1;
			free_tokens(tokens);
			return (NULL);
		}
	}
	if (!analyze_tokens(tokens))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		shell->exit_status = 1;
		free_tokens(tokens);
		return (NULL);
	}
	print_tokens(tokens);
	return (tokens);
}
