/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 01:55:32 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 12:23:38 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig_status = 0;

void	sigint_handler(int sig)
{
	g_sig_status = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_heredoc_handler(int sig)
{
	g_sig_status = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	print_signal_error(int sig)
{
	if (sig == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	else if (sig == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	else if (sig == SIGSEGV)
		write(STDERR_FILENO, "Segmentation fault (core dumped)\n", 33);
	else if (sig == SIGABRT)
		write(STDERR_FILENO, "Aborted (core dumped)\n", 22);
	else if (sig == SIGBUS)
		write(STDERR_FILENO, "Bus error (core dumped)\n", 24);
	else if (sig == SIGFPE)
		write(STDERR_FILENO, "Floating point exception (core dumped)\n", 39);
	else if (sig == SIGILL)
		write(STDERR_FILENO, "Illegal instruction (core dumped)\n", 34);
	else if (sig == SIGSYS)
		write(STDERR_FILENO, "Bad system call (core dumped)\n", 31);
}
