/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:01:18 by nsahakya          #+#    #+#             */
/*   Updated: 2025/11/01 19:07:04 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/expander.h"

void	execute_subshell_in_child(t_ast_node *node, t_shell *shell)
{
	shell->is_interactive = false;
	shell->process_depth++;
	if (expand_subshell(node, shell))
		exit_shell_with_error(shell, NULL, 1);
	if (node->redirect_files && handle_redirects(node->redirect_files) == -1)
		exit_shell_with_error(shell, NULL, 1);
	shell->exit_status = execute_ast(node->left, shell);
	exit_shell(shell);
}

int	wait_for_child(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	return (shell->exit_status);
}

int	handle_subshell_fork_error(t_shell *shell)
{
	shell_perror("fork failed");
	shell->exit_status = 1;
	return (shell->exit_status);
}
