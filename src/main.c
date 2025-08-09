#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argc;
	(void)argv;

	t_shell shell;
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
		tokenize_input(&shell);
		free(shell.input);
	}
	return (0);
}