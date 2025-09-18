#include "../../includes/ast.h"

int	execute_ast(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (execute_command(node, shell));
	else if (node->type == NODE_PIPE)
		return (execute_pipe(node, shell));
	else if (node->type == NODE_AND || node->type == NODE_OR)
		return (execute_logical(node, shell));
	else if (node->type == NODE_SUBSHELL)
		return (execute_subshell(node, shell));
	else
		return (1);
}

int	execute_command(t_ast_node *node, t_shell *shell)
{
	pid_t	pid;
	char	*command_path;

	if (!node || !node->args || !node->args[0])
		return (1);
	command_path = find_command_path(node->args[0], shell->env->data);
	if (!command_path)
		return (handle_command_not_found(node, shell));
	pid = fork();
	if (pid == 0)
	{
		handle_cmd_child(node, command_path, shell);
		exit(127);
	}
	else if (pid > 0)
		return (handle_cmd_parent(pid, command_path, shell));
	else
		return (handle_command_exec_fork_error(command_path, shell));
}

int	execute_pipe(t_ast_node *node, t_shell *shell)
{
	int		pipefds[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!node || !node->left || !node->right || pipe(pipefds) == -1)
		return (1);
	left_pid = fork_left_child(node, pipefds, shell);
	if (left_pid < 0)
		return (close_fds_return_error(pipefds));
	right_pid = fork_right_pid(node, pipefds, shell);
	if (right_pid < 0)
		return (close_fds_return_error(pipefds));
	close_fds(pipefds);
	return (wait_for_children(left_pid, right_pid, shell));
}

int	execute_logical(t_ast_node *node, t_shell *shell)
{
	if (!node || !node->left || !node->right)
		return (1);
	if (node->type == NODE_AND)
		return (execute_and(node, shell));
	else if (node->type == NODE_OR)
		return (execute_or(node, shell));
	return (1);
}

int	execute_subshell(t_ast_node *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (!node || !node->left)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (node->redirect_files
			&& handle_redirects(node->redirect_files) == -1)
			exit(1);
		exit(execute_ast(node->left, shell));
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
		return (shell->exit_status);
	}
	else
	{
		perror("fork failed");
		shell->exit_status = 1;
		return (1);
	}
}
