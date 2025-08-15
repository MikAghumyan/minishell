#include "../../includes/minishell.h"

int	process_single_char(t_shell *shell, size_t *i, t_token **tokens)
{
	if (shell->input[*i] == ' ' || shell->input[*i] == '\t')
		(*i)++;
	else if (shell->input[*i] == '\'' || shell->input[*i] == '\"')
	{
		if (add_quote_token(tokens, shell->input, i) == -1)
			return (ft_putstr_fd("minishell: tokenization error\n", 2), -1);
	}
	else if (is_operator(shell->input[*i]))
	{
		if (add_operator_token(tokens, shell->input, i) == -1)
			return (ft_putstr_fd("minishell: tokenization error\n", 2), -1);
	}
	else
	{
		if (add_word_token(tokens, shell->input, i) == -1)
			return (ft_putstr_fd("minishell: tokenization error\n", 2), -1);
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
	print_tokens(tokens);
	return (tokens);
}
