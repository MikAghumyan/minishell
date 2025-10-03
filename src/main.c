/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:17 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/02 20:28:47 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ast.h"
#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_ast_node	*ast;

	(void)envp;
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
			ast = build_ast(shell.tokens);
			if (ast)
			{
				printf("\n=== AST TREE ===\n");
				print_ast(ast, 0);
				printf("================\n\n");
				execute_ast(ast, &shell);
				printf("Exit status: %d\n", shell.exit_status);
				free_ast(ast);
			}
		}
		else
			shell.exit_status = 1;
		handle_clear_input(&shell);
	}
	handle_exit(&shell);
	return (0);
}
