#include "../../includes/ast.h"

char  **collect_ast_arguments(t_token **tokens, int *arg_count)
{
    char  **args;
    int   count;
    
    args = NULL;
    count = 0;
    
    while (*tokens && (*tokens)->type == TOKEN_WORD)
    {
        args = ft_realloc(args, sizeof(char*) * (count + 1), sizeof(char*) * (count + 2));
        if (!args)
            return (NULL);
        args[count] = ft_strdup((*tokens)->value);
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

t_ast_node  *ast_parse_simple_command(t_token **tokens)
{
    t_ast_node  *cmd_node;
    char        **args;
    int         arg_count;
    
    args = collect_ast_arguments(tokens, &arg_count);
    if (arg_count > 0)
    {
        cmd_node = create_ast_node(NODE_COMMAND);
        cmd_node->args = args;
        return (cmd_node);
    }
    return (NULL);
}

/*t_ast_node  *create_redirect_ast_node(t_token *token)
{
    if (token->type == TOKEN_REDIRECT_IN)
        return (create_ast_node(NODE_REDIRECT_IN));
    else if (token->type == TOKEN_REDIRECT_OUT)
        return (create_ast_node(NODE_REDIRECT_OUT));      no need anymore maybe
    else if (token->type == TOKEN_APPEND)
        return (create_ast_node(NODE_APPEND));
    else if (token->type == TOKEN_HEREDOC)
        return (create_ast_node(NODE_HEREDOC));
    return (NULL);
}*/

t_ast_node  *ast_parse_redirections(t_token **tokens, t_ast_node *cmd_node)
{
    t_ast_node  *redirect_node;
    
    while (*tokens && is_redirect_ast_token(*tokens))
    {
        *tokens = (*tokens)->next;
        if (*tokens && (*tokens)->type == TOKEN_WORD)
        {
            if (add_redirect_file(cmd_node, (*tokens)->value) == -1)
            {
                ft_putstr_fd("minishell: memory allocation error\n", 2);
                return (cmd_node);
            }
            *tokens = (*tokens)->next;
        }
        else
        {
            ft_putstr_fd("minishell: syntax error\n", 2);
            break;
        }
    }
    return (cmd_node);
}