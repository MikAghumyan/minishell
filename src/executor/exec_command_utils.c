/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:00:17 by nsahakya          #+#    #+#             */
/*   Updated: 2025/11/04 20:31:17 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	handle_command_not_found(t_ast_node *node, char *cmd_path, t_shell *shell)
{
	if (!node->args->data)
		return (shell->exit_status = 0);
	if (!node->args->data[0] || !node->args->data[0][0])
	{
		if (!node->args->data[0] && node->redirect_files)
			return (shell->exit_status = 0);
		else
		{
			shell_puterror("", "command not found");
			free(cmd_path);
			return (shell->exit_status = 127);
		}
	}
	if (!cmd_path || access(cmd_path, F_OK) == -1)
	{
		shell_puterror(node->args->data[0], "command not found");
		free(cmd_path);
		return (shell->exit_status = 127);
	}
	return (shell->exit_status = 0);
}

void	handle_cmd_child(t_ast_node *node, char *cmd_path, t_shell *shell)
{
	shell->process_depth++;
	if (node->redirect_files && handle_redirects(node->redirect_files) == -1)
		exit_shell_with_error(shell, NULL, 1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd_path && node->redirect_files)
		exit(0);
	execve(cmd_path, node->args->data, shell->env->data);
	free(cmd_path);
	if (errno == EACCES)
		shell->exit_status = 126;
	else if (errno == ENOENT)
		shell->exit_status = 127;
	else
		shell->exit_status = 126;
	exit_shell_with_error(shell, node->args->data[0], shell->exit_status);
}

int	handle_cmd_builtin(t_ast_node *node, t_builtin_func *func, t_shell *shell)
{
	int	builtin_status;

	shell->saved_fds[1] = dup(STDOUT_FILENO);
	shell->saved_fds[0] = dup(STDIN_FILENO);
	if (shell->saved_fds[0] == -1 || shell->saved_fds[1] == -1)
		return (shell_perror("dup error"), 1);
	if (node->redirect_files && handle_redirects(node->redirect_files) == -1)
	{
		dup2(shell->saved_fds[1], STDOUT_FILENO);
		dup2(shell->saved_fds[0], STDIN_FILENO);
		return (close_shell_fds(shell), shell->exit_status = 1);
	}
	builtin_status = func((const char **)node->args->data, shell);
	if (dup2(shell->saved_fds[1], STDOUT_FILENO) == -1
		|| dup2(shell->saved_fds[0], STDIN_FILENO) == -1)
		return (close_shell_fds(shell), shell_perror("dup error"), 1);
	close_shell_fds(shell);
	return (builtin_status);
}

int	handle_cmd_parent(pid_t pid, char *command_path, t_shell *shell)
{
	int	status;

	free(command_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		shell->interrupted = true;
		print_signal_error(WTERMSIG(status));
	}
	return (shell->exit_status);
}

int	handle_command_exec_fork_error(char *command_path, t_shell *shell)
{
	free(command_path);
	shell_perror("fork failed");
	shell->exit_status = 1;
	return (shell->exit_status);
}
