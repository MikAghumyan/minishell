/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahakya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:01:02 by nsahakya          #+#    #+#             */
/*   Updated: 2025/10/21 13:01:03 by nsahakya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

pid_t	fork_left_child(t_ast_node *node, int *pipefds, t_shell *shell)
{
	pid_t	left_pid;

	left_pid = fork();
	if (left_pid == 0)
	{
		shell->is_interactive = false;
		handle_left_pid(pipefds);
		shell->exit_status = execute_ast(node->left, shell);
		exit_shell(shell);
	}
	if (left_pid < 0)
		return (-1);
	return (left_pid);
}

pid_t	fork_right_pid(t_ast_node *node, int *pipefds, t_shell *shell)
{
	pid_t	right_pid;

	right_pid = fork();
	if (right_pid == 0)
	{
		shell->is_interactive = false;
		handle_right_pid(pipefds);
		shell->exit_status = execute_ast(node->right, shell);
		exit_shell(shell);
	}
	if (right_pid < 0)
		return (-1);
	return (right_pid);
}

int	wait_for_children(pid_t left_pid, pid_t right_pid, t_shell *shell)
{
	int	status;

	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	return (shell->exit_status);
}
