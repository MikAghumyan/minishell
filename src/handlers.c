#include "../includes/minishell.h"

void	handle_clear_input(t_shell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
}

void	handle_exit(t_shell *shell)
{
	handle_clear_input(shell);
	env_free(&shell->env);
	exit(shell->exit_status);
}