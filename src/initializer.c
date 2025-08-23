#include "../includes/minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->env = env_init(envp);
	// TODO handle error
	shell->exit_status = 0;
}