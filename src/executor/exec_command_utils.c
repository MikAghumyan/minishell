#include "../../includes/executor.h"

int	handle_command_not_found(t_ast_node *node, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	if (node && node->args && node->args[0])
		ft_putstr_fd(node->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	shell->exit_status = 127;
	return (shell->exit_status);
}

void	handle_cmd_child(t_ast_node *node, char *cmd_path, t_shell *shell)
{
	if (node->redirect_files && handle_redirects(node->redirect_files) == -1)
		exit_shell_with_error(shell, "minishell: redirection error", 1);
	execve(cmd_path, node->args, shell->env->data);
	exit_shell_with_error(shell, "minishell: execve error", 127);
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
