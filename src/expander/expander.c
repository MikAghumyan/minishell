/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:44:34 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/23 19:44:35 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

int	start_expander(t_shell *shell)
{
	t_expander	expander;

	expander.shell = shell;
	expander.syserror = false;
	expander.interrupted = false;
	shell->exit_status = process_expander(shell->ast, &expander);
	if (expander.syserror)
		exit_shell_with_error(shell, "system error", 1);
	return (shell->exit_status);
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

int	expand_subshell(t_ast_node *node, t_expander *expander)
{
	if (!node || !node->left)
		return (0);
	return (process_expander(node->left, expander)
		|| expand_redirections(node->redirect_files, expander));
}
