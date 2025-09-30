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
