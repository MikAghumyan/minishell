#include "../../includes/ast.h"

int	is_logical_ast_token(t_token *token)
{
	if (!token)
		return (0);
	return (token && (token->type == TOKEN_AND || token->type == TOKEN_OR));
}

int	is_redirect_ast_token(t_token *token)
{
	if (!token)
		return (0);
	return (token && (token->type >= TOKEN_REDIRECT_IN
			&& token->type <= TOKEN_HEREDOC));
}

int	is_subshell_ast_token(t_token *token)
{
	if (!token)
		return (0);
	return (token && token->type == TOKEN_LPAREN);
}

int	is_sub_lr_ast_token(t_token *token)
{
	if (!token)
		return (0);
	return (token && (token->type == TOKEN_LPAREN
			|| token->type == TOKEN_RPAREN));
}

int	is_logicpipe_ast_token(t_token *token)
{
	if (!token)
		return (0);
	return (token && (token->type == TOKEN_AND || token->type == TOKEN_OR
			|| token->type == TOKEN_PIPE));
}
