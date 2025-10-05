#include "../../includes/ast.h"
#include "../../includes/minishell.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID || token->type == TOKEN_WORD
			|| is_sub_lr_ast_token(token)));
}

t_ast_node	*ast_parse_subshell(t_parser *parser)
{
	t_ast_node	*subshell_node;

	subshell_node = ast_init_subshell(parser);
	if (!subshell_node)
		return (NULL);
	while (parser->tokens && !is_logicpipe_ast_token(parser->tokens))
	{
		if (is_unexpected_token(parser->tokens))
		{
			free_ast(subshell_node);
			return (NULL);
		}
		parser->tokens = parser->tokens->next;
	}
	return (subshell_node);
}

t_ast_node	*ast_init_subshell(t_parser *parser)
{
	t_ast_node	*subshell_node;

	if (!parser || !parser->tokens)
		return (NULL);
	parser->tokens = parser->tokens->next; // skip '('
	parser->subshell_depth++;
	subshell_node = create_ast_node(NODE_SUBSHELL);
	if (!subshell_node)
		return (NULL);
	subshell_node->left = ast_parse_logical(parser);
	if (!subshell_node->left)
		return (free_ast(subshell_node), NULL);
	if (parser->tokens && parser->tokens->type == TOKEN_RPAREN)
	{
		parser->tokens = parser->tokens->next; // skip ')'
		parser->subshell_depth--;
	}
	else // No closing parenthesis
		return (free_ast(subshell_node), NULL);
	subshell_node->redirect_files = collect_ast_redirects(parser->tokens);
	return (subshell_node);
}
