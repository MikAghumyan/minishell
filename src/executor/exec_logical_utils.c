/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahakya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:00:37 by nsahakya          #+#    #+#             */
/*   Updated: 2025/10/21 13:00:39 by nsahakya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	execute_and(t_ast_node *node, t_shell *shell)
{
	int	left_res;
	int	right_res;

	if (!node || !node->left || !node->right || !shell)
		return (1);
	left_res = execute_ast(node->left, shell);
	if (left_res == 0)
	{
		right_res = execute_ast(node->right, shell);
		return (right_res);
	}
	else
		return (left_res);
}

int	execute_or(t_ast_node *node, t_shell *shell)
{
	int	left_res;
	int	right_res;

	if (!node || !node->left || !node->right || !shell)
		return (1);
	left_res = execute_ast(node->left, shell);
	if (left_res == 0)
		return (left_res);
	else
	{
		right_res = execute_ast(node->right, shell);
		return (right_res);
	}
}
