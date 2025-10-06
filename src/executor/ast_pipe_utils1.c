#include "../../includes/ast.h"

int	close_fds_return_error(int *pipefds)
{
	close(pipefds[0]);
	close(pipefds[1]);
	perror("fork failed");
	return (1);
}

void	close_fds(int *pipefds)
{
	close(pipefds[0]);
	close(pipefds[1]);
}

void	handle_left_pid(int *pipefds)
{
	dup2(pipefds[1], 1);
	close(pipefds[1]);
	close(pipefds[0]);
}

void	handle_right_pid(int *pipefds)
{
	dup2(pipefds[0], 0);
	close(pipefds[0]);
	close(pipefds[1]);
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
