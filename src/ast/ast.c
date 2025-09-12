#include "../../includes/ast.h"

t_ast_node  *create_ast_node(e_node_type type)
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->args = NULL;
    node->redirect_files = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void    free_ast(t_ast_node *node)
{
    int i;

    if (!node)
        return ;
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
    free_redirects(node);
    free_ast(node->right);
    free_ast(node->left);
    free(node);
}

static void    free_redirects(t_ast_node *node)
{
    int i;

    if (node->redirect_files)
    {
        i = 0;
        while (node->redirect_files[i])
        {
            free(node->redirect_files[i]);
            i++;
        }
        free(node->redirect_files);
    }
    
}

void print_ast(t_ast_node *node, int depth)
{
    int i;

    if (!node)
        return ;
    
    for (i = 0; i < depth; i++)
        printf("  ");
    
    switch (node->type)
    {
        case NODE_COMMAND:
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
            if (node->redirect_files)
            {
                printf("(redirects: ");
                i = 0;
                while (node->redirect_files[i])
                {
                    printf("%s ", node->redirect_files[i]);
                    i++;
                }
                printf(")");
            }
            break;
        case NODE_PIPE:
            printf("PIPE");
            break;
        case NODE_AND:
            printf("AND");
            break;
        case NODE_OR:
            printf("OR");
            break;
        case NODE_SUBSHELL:
            printf("SUBSHELL");
            break;
        default:
            printf("UNKNOWN");
    }
    printf("\n");
    
    if (node->left)
        print_ast(node->left, depth + 1);
    if (node->right)
        print_ast(node->right, depth + 1);
}