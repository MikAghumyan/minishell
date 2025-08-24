#include "../../includes/ast.h"

t_ast_node  *build_ast(t_token *tokens)
{
    if (!tokens)
        return (NULL);
    return (parse_logical(&tokens));
}

t_ast_node  *parse_logical(t_token **tokens) //&& ||
{
    t_ast_node  *left; //left command
    t_ast_node  *operator_node;

    left = parse_pipeline(tokens);
    while (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR)) //handilng tokens in cycle
    {
        if ((*tokens)->type == TOKEN_AND)  //creating operator node
            operator_node = create_node(NODE_AND);
        else
            operator_node = create_node(NODE_OR);
        *tokens = (*tokens)->next; //skip operator
        operator_node->left = left;  
        operator_node->right = parse_pipeline(tokens);
        left = operator_node;
    } 
    return (left);
}

t_ast_node  *parse_pipeline(t_token **tokens) // |
{
    t_ast_node  *left;
    t_ast_node  *pipe_node;

    left = parse_command(tokens);
    while (*tokens && (*tokens)->type == TOKEN_PIPE) // the same logic as in parse_logical
    {
        pipe_node = create_node(NODE_PIPE);
        *tokens = (*tokens)->next;
        pipe_node->left = left;
        pipe_node->right = parse_command(tokens);
        left = pipe_node;
    }
    return (left);
}