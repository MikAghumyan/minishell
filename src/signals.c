#include "../includes/minishell.h"

/* global signal status - defined here to satisfy extern in header */
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