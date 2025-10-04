#include "../../includes/ast.h"
#include "../../includes/minishell.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID
			|| is_sub_lr_ast_token(token)));
}

t_ast_node	*ast_parse_command(t_token **tokens)
{
	t_ast_node	*result;

	if (!tokens || !*tokens)
		return (NULL);
	if (is_subshell_ast_token(*tokens))
		return (ast_parse_subshell(tokens));
	result = ast_init_command(tokens);
	if (!result)
		return (NULL);
	while (*tokens && !is_logicpipe_ast_token(*tokens))
	{
		if (is_unexpected_token(*tokens))
		{
			free_ast(result);
			return (NULL);
		}
		*tokens = (*tokens)->next;
	}
	return (result);
}

t_ast_node	*ast_init_command(t_token **tokens)
{
	t_ast_node	*result;

	result = malloc(sizeof(t_ast_node));
	if (!result)
		return (NULL);
	result->type = NODE_COMMAND;
	result->args = collect_ast_arguments(*tokens);
	result->redirect_files = collect_ast_redirects(*tokens);
	result->left = NULL;
	result->right = NULL;
	if (!result->args)
	{
		free(result);
		return (NULL);
	}
	return (result);
}
