/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:17 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 02:11:51 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ast.h"
#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	initialize_shell(&shell, envp);
	printf("Welcome to Minishell!\n");
	/* setup signal handlers */
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		shell.input = readline("\033[0;36mminishell\033[1m$\033[0m ");
		if (!shell.input)
			break ;
		if (shell.input[0] != '\0')
			add_history(shell.input);
		// TODO HANDLE ADD_HISTORY'S CLEAN AT THE END
		if (g_sig_status)
		{
			shell.exit_status = 128 + g_sig_status;
			g_sig_status = 0;
		}
		shell.tokens = tokenize_input(&shell);
		if (shell.tokens)
		{
			shell.ast = build_ast(&shell);
			free_tokens(shell.tokens);
			shell.tokens = NULL;
			if (shell.ast)
			{
				signal(SIGINT, SIG_IGN);
				shell.exit_status = execute_ast(shell.ast, &shell);
				free_ast(shell.ast);
				shell.ast = NULL;
				signal(SIGINT, sigint_handler);
			}
			if (shell.exit_status != 0)
				printf("%sExit status: %d%s\n", RED, shell.exit_status, RESET);
			else
				printf("%sExit status: %d%s\n", GREEN, shell.exit_status,
					RESET);
		}
		free(shell.input);
		shell.input = NULL;
	}
	printf("exit\n");
	exit_shell(&shell);
	return (0);
}
