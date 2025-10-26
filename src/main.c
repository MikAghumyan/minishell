/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:17 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 14:40:34 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"
#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	initialize_shell(&shell, envp);
	if (shell.is_interactive)
	{
		printf("\e[1;32mWelcome back, %s! 🐚 Minishell ready.\e[0m\n",
			env_get_value("USER", shell.env));
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		shell_loop_interactive(&shell);
		printf("exit\n");
	}
	else
		shell_loop_non_interactive(&shell);
	exit_shell(&shell);
	return (0);
}
