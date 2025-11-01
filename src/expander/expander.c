/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:44:34 by maghumya          #+#    #+#             */
/*   Updated: 2025/11/01 14:18:26 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

int	start_expander(t_shell *shell)
{
	shell->exit_status = process_expander(shell->ast, shell);
	if (shell->syserror)
		exit_shell_with_error(shell, "system error", 1);
	return (shell->exit_status);
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

int	expand_command(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return (0);
	/* First expand command arguments, then redirections */
	if (expand_arguments(&node->args, shell))
		return (1);
	return (expand_redirections(node->redirect_files, shell));
}

int	expand_subshell(t_ast_node *node, t_shell *shell)
{
	if (!node || !node->left)
		return (0);
	return (process_expander(node->left, shell)
		|| expand_redirections(node->redirect_files, shell));
}
