#include "../../includes/ast.h"

static void	free_redirects(t_ast_node *node)
{
	t_redirect	*current;
	t_redirect	*next;

	if (!node->redirect_files)
		return ;
	current = node->redirect_files;
	while (current)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		free(current);
		current = next;
	}
	node->redirect_files = NULL;
}

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

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

void	free_ast(t_ast_node *node)
{
	int	i;

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

void	print_ast(t_ast_node *node, int depth) //no need here to fix norme errors, it's just a debug function
{
	int	i;
	t_redirect	*redirect;

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
                redirect = node->redirect_files;
                while (redirect)
                {
                    printf("[%d:%s] ", redirect->type, redirect->filename);
                    redirect = redirect->next;
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
