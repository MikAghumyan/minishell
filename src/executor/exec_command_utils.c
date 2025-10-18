#include "../../includes/executor.h"

int	handle_command_not_found(t_ast_node *node, char *cmd_path, t_shell *shell)
{
	if (!cmd_path || access(cmd_path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		if (node && node->args && node->args[0])
			ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (shell->exit_status = 127);
	}
	return (shell->exit_status = 0);
}

void	handle_cmd_child(t_ast_node *node, char *cmd_path, t_shell *shell)
{
	if (node->redirect_files && handle_redirects(node->redirect_files) == -1)
		exit_shell_with_error(shell, "minishell: redirection error", 1);
	execve(cmd_path, node->args, shell->env->data);
	if (errno == EACCES)
		shell->exit_status = 126;
	else if (errno == ENOENT)
		shell->exit_status = 127;
	else
		shell->exit_status = 126;
	exit_shell_with_error(shell, "minishell: execve error", shell->exit_status);
}

int	handle_cmd_builtin(t_ast_node *node, t_builtin_func *func, t_shell *shell)
{
	int	builtin_status;

	shell->saved_fds[1] = dup(STDOUT_FILENO);
	shell->saved_fds[0] = dup(STDIN_FILENO);
	if (shell->saved_fds[0] == -1 || shell->saved_fds[1] == -1)
		exit_shell_with_error(shell, "minishell: dup error", 1);
	if (node->redirect_files && handle_redirects(node->redirect_files) == -1)
		exit_shell_with_error(shell, "minishell: redirection error", 1);
	builtin_status = func((const char **)node->args, shell);
	if (dup2(shell->saved_fds[1], STDOUT_FILENO) == -1
		|| dup2(shell->saved_fds[0], STDIN_FILENO) == -1)
		exit_shell_with_error(shell, "minishell: dup error", 1);
	close(shell->saved_fds[1]);
	close(shell->saved_fds[0]);
	shell->saved_fds[0] = -1;
	shell->saved_fds[1] = -1;
	return (builtin_status);
}

int	handle_cmd_parent(pid_t pid, char *command_path, t_shell *shell)
{
	int	status;

	free(command_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}

int	handle_command_exec_fork_error(char *command_path, t_shell *shell)
{
	free(command_path);
	perror("fork failed");
	shell->exit_status = 1;
	return (shell->exit_status);
}
