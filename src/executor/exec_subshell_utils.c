#include "../../includes/executor.h"

void	execute_subshell_in_child(t_ast_node *node, t_shell *shell)
{
	if (node->redirect_files && handle_redirects(node->redirect_files) == -1)
		exit_shell_with_error(shell, "minishell: redirection error", 1);
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
	perror("fork failed");
	shell->exit_status = 1;
	return (shell->exit_status);
}
