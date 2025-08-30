#include "../../includes/ast.h"

int execute_ast(t_ast_node *node, t_shell *shell)
{
    if (!node)
        return (0);
    if (node->type == NODE_COMMAND)
        return (execute_command(node, shell));
    else if (node->type == NODE_PIPE)
        return (execute_pipe(node, shell));
    else if (node->type == NODE_AND || node->type == NODE_OR)
        return (execute_pipe(node, shell));
    else if (node->type >= NODE_REDIRECT_IN && node->type <= NODE_HEREDOC)
        return (execute_redirect(node, shell));
    else if (node->type == NODE_SUBSHELL)
        return (execute_subshell(node, shell));
    else
        return (1);
}