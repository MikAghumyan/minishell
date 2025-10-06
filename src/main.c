/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:17 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/06 15:32:12 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	initialize_shell(&shell, envp);
	printf("Welcome to Minishell!\n");
	while (true)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
			break ;
		if (shell.input[0] != '\0')
			add_history(shell.input);
		// TODO HANDLE ADD_HISTORY'S CLEAN AT THE END
		shell.tokens = tokenize_input(&shell);
		if (shell.tokens)
		{
			shell.ast = build_ast(&shell);
			if (shell.ast)
			{
				free_tokens(shell.tokens);
				shell.tokens = NULL;
				execute_ast(shell.ast, &shell);
				free_ast(shell.ast);
				shell.ast = NULL;
			}
			printf("Exit status: %d\n", shell.exit_status);
		}
		handle_clear_input(&shell);
	}
	handle_exit(&shell);
	return (0);
}
