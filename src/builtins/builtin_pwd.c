#include "../../includes/builtins.h"

int	builtin_pwd(const char **args, t_shell *shell)
{
	char *cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd");
		shell->exit_status = 1;
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
	shell->exit_status = 0;
	return (shell->exit_status);
}