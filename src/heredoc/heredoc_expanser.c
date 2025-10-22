#include "../../includes/ast.h"
#include "../../includes/expander.h"

int	expand_command(t_ast_node *node, t_shell *shell)
{
}

int	process_expander(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (expand_command(node, shell));
	else if (node->type == NODE_AND || node->type == NODE_OR
		|| node->type == NODE_PIPE)
		return (process_expander(node->left, shell),
			process_expander(node->right, shell));
	else if (node->type == NODE_SUBSHELL)
		return (expand_subshell(node, shell));
	else
		return (1);
}