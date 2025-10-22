#include "../../includes/ast.h"
#include "../../includes/expander.h"

int	start_expander(t_shell *shell)
{
	t_expander	expander;

	expander.shell = shell;
	expander.syserror = false;
	expander.interrupted = false;
	return (process_expander(shell->ast, &expander));
}

int	process_expander(t_ast_node *node, t_expander *expander)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (expand_command(node, expander));
	else if (node->type == NODE_AND || node->type == NODE_OR
		|| node->type == NODE_PIPE)
		return (process_expander(node->left, expander),
			process_expander(node->right, expander));
	else if (node->type == NODE_SUBSHELL)
		return (expand_subshell(node, expander));
	else
		return (1);
}

int	expand_command(t_ast_node *node, t_expander *expander)
{
	if (!node)
		return (0);
	return (expand_redirections(node->redirect_files, expander));
}
