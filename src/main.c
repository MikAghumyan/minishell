#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)envp;
	(void)argc;
	(void)argv;
	initialize_shell(&shell, envp);
	while (*shell.envp)
	{
		printf("%s\n", *shell.envp);
		shell.envp++;
	}
	printf("Welcome to Minishell!\n");
	while (true)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
			break ;
		shell.tokens = tokenize_input(&shell);
		handle_clear(&shell);
	}
	handle_exit(&shell);
	return (0);
}
