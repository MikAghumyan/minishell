#include "../../includes/builtins.h"
#include "../../includes/executor.h"

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
	pid_t			pid;
	char			*command_path;
	t_builtin_func	*builtin_func;

	if (!node || !node->args->data || !node->args->data[0]
		|| !node->args->data[0][0])
		return (handle_command_not_found(node, NULL, shell));
	builtin_func = return_builtin_function((const char **)node->args->data);
	if (builtin_func)
		return (handle_cmd_builtin(node, builtin_func, shell));
	command_path = find_command_path(node->args->data[0], shell->env->data);
	if (handle_command_not_found(node, command_path, shell))
		return (shell->exit_status);
	pid = fork();
	if (pid == 0)
		handle_cmd_child(node, command_path, shell);
	else if (pid > 0)
		return (handle_cmd_parent(pid, command_path, shell));
	else
		return (handle_command_exec_fork_error(command_path, shell));
	return (1);
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
	shell->exit_status = wait_for_children(left_pid, right_pid, shell);
	return (shell->exit_status);
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

	if (!node || !node->left)
		return (1);
	pid = fork();
	if (pid == 0)
		execute_subshell_in_child(node, shell);
	else if (pid > 0)
		return (wait_for_child(pid, shell));
	else
		return (handle_subshell_fork_error(shell));
	return (1);
}
