/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:50:11 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/23 19:26:47 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ast.h"
#include "../includes/executor.h"
#include "../includes/expander.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

static void	process_input(t_shell *shell)
{
	shell->interrupted = false;
	shell->syserror = false;
	shell->tokens = tokenize_input(shell);
	if (shell->tokens)
	{
		shell->ast = build_ast(shell);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		if (shell->ast)
		{
			if (shell->is_interactive)
				signal(SIGINT, SIG_IGN);
			shell->exit_status = start_expander(shell);
			if (!shell->exit_status)
				shell->exit_status = execute_ast(shell->ast, shell);
			free_ast(shell->ast, shell);
			shell->ast = NULL;
			if (shell->is_interactive)
				signal(SIGINT, sigint_handler);
		}
		if (shell->is_interactive)
			print_exit_status(shell);
	}
	free(shell->input);
	shell->input = NULL;
}

void	shell_loop_interactive(t_shell *shell)
{
	while (true)
	{
		shell->input = readline("\033[0;36mminishell\033[1m$\033[0m ");
		if (!shell->input)
			break ;
		if (shell->input[0] != '\0')
			add_history(shell->input);
		if (g_signo)
		{
			shell->exit_status = 128 + g_signo;
			g_signo = 0;
		}
		process_input(shell);
	}
	rl_clear_history();
}

void	shell_loop_non_interactive(t_shell *shell)
{
	while (true)
	{
		shell->input = get_next_line(STDIN_FILENO);
		if (!shell->input)
			break ;
		shell->input[ft_strlen(shell->input) - 1] = '\0';
		process_input(shell);
	}
}
