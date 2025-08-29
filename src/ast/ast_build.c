#include "../../includes/ast.h"
#include <stdlib.h>
#include <string.h>

t_ast_node  *build_ast(t_token *tokens)
{
    if (!tokens)
        return (NULL);
    return (ast_parse_logical(&tokens));
}

t_ast_node  *ast_parse_logical(t_token **tokens)
{
    t_ast_node  *left;
    t_ast_node  *operator_node;

    left = ast_parse_pipeline(tokens);
    while (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
    {
        if ((*tokens)->type == TOKEN_AND)
            operator_node = create_ast_node(NODE_AND);
        else
            operator_node = create_ast_node(NODE_OR);
        *tokens = (*tokens)->next;
        operator_node->left = left;
        operator_node->right = ast_parse_pipeline(tokens);
        left = operator_node;
    } 
    return (left);
}

t_ast_node  *ast_parse_pipeline(t_token **tokens)
{
    t_ast_node  *left;
    t_ast_node  *pipe_node;

    left = ast_parse_command(tokens);
    while (*tokens && (*tokens)->type == TOKEN_PIPE) // the same logic as in parse_logical
    {
        pipe_node = create_ast_node(NODE_PIPE);
        *tokens = (*tokens)->next;
        pipe_node->left = left;
        pipe_node->right = ast_parse_command(tokens);
        left = pipe_node;
    }
    return (left);
}

static t_ast_node  *ast_parse_subshell(t_token **tokens)
{
    t_ast_node  *subshell_node;
    
    *tokens = (*tokens)->next; // skip '('
    subshell_node = create_ast_node(NODE_SUBSHELL);
    subshell_node->left = ast_parse_logical(tokens);
    
    if (*tokens && (*tokens)->type == TOKEN_RPAREN)
        *tokens = (*tokens)->next; // skip ')'
    
    return (subshell_node);
}



t_ast_node  *ast_parse_command(t_token **tokens)
{
    t_ast_node  *cmd_node;
    
    if (is_subshell_ast_token(*tokens))
        return (ast_parse_subshell(tokens));
    
    cmd_node = ast_parse_simple_command(tokens);
    cmd_node = ast_parse_redirections(tokens, cmd_node);
    
    return (cmd_node);
}