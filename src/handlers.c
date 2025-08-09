#include "../includes/minishell.h"

void	handle_clear(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		free_tokens(shell->tokens);
}

void	handle_exit(t_shell *shell)
{
	handle_clear(shell);
	exit(shell->exit_status);
}