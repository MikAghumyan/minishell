#include "../../includes/minishell.h"

t_ast_node  *create_ast_node(t_ast_type type)
{
    t_ast_node  *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->args = NULL;
    node->filename = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void    free_ast(t_ast_node *node)
{
    int i;

    if (!node)
        return;
    if (node->args)
    {
        i = 0;
        while (node->args[i])
        {
            free(node->args[i]);
            i++;
        }
        free(node->args);
    }
    if (node->filename)
        free(node->filename);
    free(node->left);
    free(node->right);
    free(node);
}

void print_ast(t_ast_node *node, int depth) //for debug
{
    int i;
    
    if (!node)
        return;
    
    for (i = 0; i < depth; i++)
        printf("  ");
    
    switch (node->type)
    {
        case AST_COMMAND:
            printf("COMMAND: ");
            if (node->args)
            {
                i = 0;
                while (node->args[i])
                {
                    printf("%s ", node->args[i]);
                    i++;
                }
            }
            printf("\n");
            break;
        case AST_PIPE:
            printf("PIPE\n");
            break;
        case AST_AND:
            printf("AND\n");
            break;
        case AST_OR:
            printf("OR\n");
            break;
        case AST_REDIRECT_IN:
            printf("REDIRECT_IN: %s\n", node->filename ? node->filename : "NULL");
            break;
        case AST_REDIRECT_OUT:
            printf("REDIRECT_OUT: %s\n", node->filename ? node->filename : "NULL");
            break;
        case AST_APPEND:
            printf("APPEND: %s\n", node->filename ? node->filename : "NULL");
            break;
        case AST_HEREDOC:
            printf("HEREDOC: %s\n", node->filename ? node->filename : "NULL");
            break;
    }
    
    if (node->left)
        print_ast(node->left, depth + 1);
    if (node->right)
        print_ast(node->right, depth + 1);
}