#include "../../includes/ast.h"

t_ast_node  *create_ast_node(e_node_type type)
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->args = NULL;
    node->redirect_file = NULL;
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
    if (node->redirect_file)
        free(node->redirect_file);
    free_ast(node->right);
    free_ast(node->left);
    free(node);
}


void	print_ast(t_ast_node *node, int depth)
{
    int	i;

    if (!node)
        return ;
    i = 0;
    while (i < depth)
    {
        printf("  ");
        i++;
    }
    if (node->type == NODE_COMMAND)
    {
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
    }
    else if (node->type == NODE_PIPE)
        printf("PIPE\n");
    else if (node->type == NODE_AND)
        printf("AND\n");
    else if (node->type == NODE_OR)
        printf("OR\n");
    else if (node->type == NODE_REDIRECT_OUT)
        printf("REDIRECT_OUT: %s\n", node->redirect_file);
    else if (node->type == NODE_REDIRECT_IN)
        printf("REDIRECT_IN: %s\n", node->redirect_file);
    else if (node->type == NODE_APPEND)
        printf("APPEND: %s\n", node->redirect_file);
    else if (node->type == NODE_HEREDOC)
        printf("HEREDOC: %s\n", node->redirect_file);
    else if (node->type == NODE_SUBSHELL)
        printf("SUBSHELL\n");
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}