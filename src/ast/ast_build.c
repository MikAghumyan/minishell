#include "../../includes/ast.h"

t_ast_node	*build_ast(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (ast_parse_logical(&tokens));
}

t_ast_node	*ast_parse_logical(t_token **tokens)
{
	t_ast_node	*left;
	t_ast_node	*operator_node;

	if (!tokens || !*tokens)
		return (NULL);
	left = ast_parse_pipeline(tokens);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		if ((*tokens)->type == TOKEN_AND)
			operator_node = create_ast_node(NODE_AND);
		else
			operator_node = create_ast_node(NODE_OR);
		if (!operator_node)
			return (free_ast(left), NULL);
		*tokens = (*tokens)->next;
		operator_node->left = left;
		operator_node->right = ast_parse_pipeline(tokens);
		left = operator_node;
		if (!operator_node->right)
			return (free_ast(left), NULL);
	}
	return (left);
}

t_ast_node	*ast_parse_pipeline(t_token **tokens)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;

	if (!tokens || !*tokens)
		return (NULL);
	left = ast_parse_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		pipe_node = create_ast_node(NODE_PIPE);
		if (!pipe_node)
			return (free_ast(left), NULL);
		*tokens = (*tokens)->next;
		pipe_node->left = left;
		pipe_node->right = ast_parse_command(tokens);
		left = pipe_node;
		if (!pipe_node->right)
			return (free_ast(left), NULL);
	}
	return (left);
}

static t_ast_node	*ast_parse_subshell(t_token **tokens)
{
	t_ast_node	*subshell_node;
	t_ast_node	*result;

	if (!tokens || !*tokens)
		return (NULL);
	*tokens = (*tokens)->next;
	subshell_node = create_ast_node(NODE_SUBSHELL);
	if (!subshell_node)
		return (NULL);
	subshell_node->left = ast_parse_logical(tokens);
	if (!subshell_node->left)
		return (free_ast(subshell_node), NULL);
	if (*tokens && (*tokens)->type == TOKEN_RPAREN)
		*tokens = (*tokens)->next;
	result = ast_parse_redirections(tokens, subshell_node);
	if (!result)
		return (free_ast(subshell_node), NULL);
	return (result);
}

t_ast_node	*ast_parse_command(t_token **tokens)
{
	t_ast_node	*cmd_node;
	t_ast_node	*result;

	if (!tokens || !*tokens)
		return (NULL);
	if (is_subshell_ast_token(*tokens))
		return (ast_parse_subshell(tokens));
	cmd_node = ast_parse_simple_command(tokens);
	if (!cmd_node)
		return (NULL);
	result = ast_parse_redirections(tokens, cmd_node);
	if (!result)
	{
		free_ast(cmd_node);
		ft_putstr_fd("minishell: redirect parsing failed\n", 2);
		return (NULL);
	}
	return (result);
}
