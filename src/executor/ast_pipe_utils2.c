#include "../../includes/ast.h"

int	type_pipe_error_and_return(void)
{
	perror("pipe failed");
	return (1);
}

pid_t	fork_left_child(t_ast_node *node, int *pipefds, t_shell *shell)
{
	pid_t	left_pid;

	left_pid = fork();
	if (left_pid == 0)
	{
		handle_left_pid(pipefds);
		exit(execute_ast(node->left, shell));
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
		handle_right_pid(pipefds);
		exit(execute_ast(node->right, shell));
	}
	if (right_pid < 0)
		return (-1);
	return (right_pid);
}
