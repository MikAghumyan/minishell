/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:44:34 by maghumya          #+#    #+#             */
/*   Updated: 2025/11/01 18:39:54 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

int	expand_command(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return (shell->exit_status = 0);
	if (expand_arguments(&node->args, shell))
		return (shell->exit_status = 1);
	return (shell->exit_status = expand_redirections(node->redirect_files,
			shell));
}

int	expand_subshell(t_ast_node *node, t_shell *shell)
{
	if (!node || !node->left)
		return (shell->exit_status = 0);
	return (shell->exit_status = expand_redirections(node->redirect_files,
			shell));
}
