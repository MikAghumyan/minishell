#include "../../includes/ast.h"

int  is_logical_token(t_token *token)
{
    return (token && (token->type == TOKEN_AND || token->type == TOKEN_OR));
}

int  is_redirect_token(t_token *token)
{
    return (token && (token->type == TOKEN_REDIRECT_IN || 
                     token->type == TOKEN_REDIRECT_OUT ||
                     token->type == TOKEN_APPEND || 
                     token->type == TOKEN_HEREDOC));
}

int  is_subshell_token(t_token *token)
{
    return (token && token->type == TOKEN_LPAREN);
}

