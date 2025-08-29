#include "../../includes/ast.h"

char  **collect_arguments(t_token **tokens, int *arg_count)
{
    char  **args;
    int   count;
    
    args = NULL;
    count = 0;
    
    while (*tokens && (*tokens)->type == TOKEN_WORD)
    {
        args = realloc(args, sizeof(char*) * (count + 2));
        if (!args)
            return (NULL);
        args[count] = strdup((*tokens)->value);
        if (!args[count])
            return (NULL);
        count++;
        *tokens = (*tokens)->next;
    }
    
    if (args)
        args[count] = NULL;
    *arg_count = count;
    return (args);
}

t_ast_node  *parse_simple_command(t_token **tokens)
{
    t_ast_node  *cmd_node;
    char        **args;
    int         arg_count;
    
    args = collect_arguments(tokens, &arg_count);
    if (arg_count > 0)
    {
        cmd_node = create_node(NODE_COMMAND);
        cmd_node->args = args;
        return (cmd_node);
    }
    return (NULL);
}

t_ast_node  *create_redirect_node(t_token *token)
{
    if (token->type == TOKEN_REDIRECT_IN)
        return (create_node(NODE_REDIRECT_IN));
    else if (token->type == TOKEN_REDIRECT_OUT)
        return (create_node(NODE_REDIRECT_OUT));
    else if (token->type == TOKEN_APPEND)
        return (create_node(NODE_APPEND));
    else if (token->type == TOKEN_HEREDOC)
        return (create_node(NODE_HEREDOC));
    return (NULL);
}

t_ast_node  *parse_redirections(t_token **tokens, t_ast_node *cmd_node)
{
    t_ast_node  *redirect_node;
    
    while (*tokens && is_redirect_token(*tokens))
    {
        redirect_node = create_redirect_node(*tokens);
        *tokens = (*tokens)->next;
        
        if (*tokens && (*tokens)->type == TOKEN_WORD)
        {
            redirect_node->redirect_file = strdup((*tokens)->value);
            *tokens = (*tokens)->next;
            redirect_node->left = cmd_node;
            cmd_node = redirect_node;
        }
    }
    return (cmd_node);
}