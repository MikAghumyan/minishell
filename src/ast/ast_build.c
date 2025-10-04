#include "../../includes/ast.h"

t_ast_node	*build_ast(t_token *tokens)
{
	t_parser	parser;
	t_ast_node	*result;

	if (!tokens)
		return (NULL);
	parser.tokens = tokens;
	parser.subshell_depth = 0;
	result = ast_parse_logical(&parser);
	if (parser.tokens)
		printf("minishell: syntax error FROM AST $%s\n", parser.tokens->value);
	return (result);
}

t_ast_node	*ast_parse_logical(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*operator_node;

	if (!parser || !parser->tokens)
		return (NULL);
	left = ast_parse_pipeline(parser);
	if (!left)
		return (NULL);
	while (parser->tokens && (parser->tokens->type == TOKEN_AND
			|| parser->tokens->type == TOKEN_OR))
	{
		if (parser->tokens->type == TOKEN_AND)
			operator_node = create_ast_node(NODE_AND);
		else
			operator_node = create_ast_node(NODE_OR);
		if (!operator_node)
			return (free_ast(left), NULL);
		parser->tokens = parser->tokens->next;
		operator_node->left = left;
		operator_node->right = ast_parse_pipeline(parser);
		left = operator_node;
		if (!operator_node->right)
			return (free_ast(left), NULL);
	}
	return (left);
}

t_ast_node	*ast_parse_pipeline(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;

	if (!parser || !parser->tokens)
		return (NULL);
	left = ast_parse_command(parser);
	if (!left)
	{
		printf("RETURNING NULL FROM PIPELINE\n");
		return (NULL);
	}
	while (parser->tokens && parser->tokens->type == TOKEN_PIPE)
	{
		pipe_node = create_ast_node(NODE_PIPE);
		if (!pipe_node)
			return (free_ast(left), NULL);
		parser->tokens = parser->tokens->next;
		pipe_node->left = left;
		pipe_node->right = ast_parse_command(parser);
		left = pipe_node;
		if (!pipe_node->right)
			return (free_ast(left), NULL);
	}
	return (left);
}
