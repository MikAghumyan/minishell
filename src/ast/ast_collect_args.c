#include "../../includes/ast.h"
#include "../../includes/minishell.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID
			|| is_sub_lr_ast_token(token)));
}

static size_t	count_args(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens && !is_logicpipe_ast_token(tokens)
		&& !is_unexpected_token(tokens))
	{
		if (tokens->type == TOKEN_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

char	**collect_ast_arguments(t_token *tokens)
{
	char	**args;
	size_t	count;
	size_t	i;

	count = count_args(tokens);
	if (count == 0)
		return (NULL);
	args = ft_calloc(sizeof(char *), (count + 1));
	if (!args)
		return (NULL);
	args[count] = NULL;
	i = 0;
	while (tokens && !is_logicpipe_ast_token(tokens)
		&& !is_unexpected_token(tokens))
	{
		if (tokens->type == TOKEN_WORD)
		{
			args[i] = ft_strdup(tokens->value);
			if (!args[i])
				return (ft_free_array((void ***)&args), NULL);
			i++;
		}
		tokens = tokens->next;
	}
	return (args);
}
