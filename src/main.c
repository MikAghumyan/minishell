/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:17 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/10 16:30:46 by maghumya         ###   ########.fr       */
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
	while (true)
	{
		shell.input = readline("\033[0;36mminishell>\033[0m ");
		if (!shell.input)
			break ;
		if (shell.input[0] != '\0')
			add_history(shell.input);
		// TODO HANDLE ADD_HISTORY'S CLEAN AT THE END
		shell.tokens = tokenize_input(&shell);
		if (shell.tokens)
		{
			shell.ast = build_ast(&shell);
			free_tokens(shell.tokens);
			shell.tokens = NULL;
			if (shell.ast)
			{
				shell.exit_status = execute_ast(shell.ast, &shell);
				free_ast(shell.ast);
				shell.ast = NULL;
			}
			printf("Exit status: %d\n", shell.exit_status);
		}
		free(shell.input);
		shell.input = NULL;
	}
	exit_shell(&shell);
	return (0);
}
