#include "../../includes/ast.h"

static t_ast_node	*handle_logical_node(t_parser *parser, t_ast_node *left)
{
	t_ast_node	*operator_node;
	t_token		*current_token;

	if (parser->tokens->type == TOKEN_AND)
		operator_node = create_ast_node(NODE_AND);
	else
		operator_node = create_ast_node(NODE_OR);
	if (!operator_node)
		return (free_ast(left), NULL);
	current_token = parser->tokens;
	parser->tokens = parser->tokens->next;
	operator_node->left = left;
	operator_node->right = ast_parse_pipeline(parser);
	left = operator_node;
	if (!operator_node->right)
	{
		if (!parser->tokens)
			parser->tokens = current_token;
		return (free_ast(left), NULL);
	}
	return (left);
}

t_ast_node	*ast_parse_logical(t_parser *parser)
{
	t_ast_node	*left;

	if (!parser || !parser->tokens)
		return (NULL);
	left = ast_parse_pipeline(parser);
	if (!left)
		return (NULL);
	while (parser->tokens && (parser->tokens->type == TOKEN_AND
			|| parser->tokens->type == TOKEN_OR))
	{
		left = handle_logical_node(parser, left);
		if (!left)
			return (NULL);
	}
	return (left);
}

static t_ast_node	*handle_pipe_node(t_parser *parser, t_ast_node *left)
{
	t_ast_node	*pipe_node;
	t_token		*current_token;

	pipe_node = create_ast_node(NODE_PIPE);
	if (!pipe_node)
		return (free_ast(left), NULL);
	current_token = parser->tokens;
	parser->tokens = parser->tokens->next;
	pipe_node->left = left;
	pipe_node->right = ast_parse_command(parser);
	left = pipe_node;
	if (!pipe_node->right)
	{
		if (!parser->tokens)
			parser->tokens = current_token;
		return (free_ast(left), NULL);
	}
	return (left);
}

t_ast_node	*ast_parse_pipeline(t_parser *parser)
{
	t_ast_node	*left;

	if (!parser || !parser->tokens)
		return (NULL);
	left = ast_parse_command(parser);
	if (!left)
		return (NULL);
	while (parser->tokens && parser->tokens->type == TOKEN_PIPE)
	{
		left = handle_pipe_node(parser, left);
		if (!left)
			return (NULL);
	}
	return (left);
}
