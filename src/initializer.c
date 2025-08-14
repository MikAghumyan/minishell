#include "../includes/minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->exit_status = 0;
}