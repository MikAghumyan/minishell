/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:20 by maghumya          #+#    #+#             */
/*   Updated: 2025/11/04 21:21:13 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ast.h"
#include "../includes/env.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	close_shell_fds(t_shell *shell)
{
	if (shell->saved_fds[0] != -1)
		close(shell->saved_fds[0]);
	if (shell->saved_fds[1] != -1)
		close(shell->saved_fds[1]);
	shell->saved_fds[0] = -1;
	shell->saved_fds[1] = -1;
}

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->env = env_init(envp);
	if (!shell->env)
		exit_shell_with_error(shell, "system error", 1);
	shell->is_interactive = isatty(STDIN_FILENO);
	if (shell->is_interactive && !env_shlvl_increment(shell->env))
		exit_shell_with_error(shell, "system error", 1);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->exit_status = 0;
	shell->saved_fds[0] = -1;
	shell->saved_fds[1] = -1;
	shell->process_depth = 0;
	shell->syserror = false;
	shell->interrupted = false;
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->input)
		free(shell->input);
	shell->input = NULL;
	if (shell->tokens)
		free_tokens(shell->tokens);
	shell->tokens = NULL;
	if (shell->ast)
		free_ast(shell->ast, shell);
	shell->ast = NULL;
	if (shell->env)
		ft_sv_free(shell->env);
	shell->env = NULL;
	close_shell_fds(shell);
	if (shell->is_interactive)
		rl_clear_history();
	if (shell->input)
		free(shell->input);
}

void	exit_shell(t_shell *shell)
{
	cleanup_shell(shell);
	exit(shell->exit_status);
}

void	exit_shell_with_error(t_shell *shell, const char *message, int errnum)
{
	if (message)
		shell_perror(message);
	shell->exit_status = errnum;
	exit_shell(shell);
}
