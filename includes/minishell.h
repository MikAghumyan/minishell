/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:36:47 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 14:06:26 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"

# define WARNING_HEREDOC "warning: here-document delimited by end-of-file"

# ifndef PATH_HEREDOC
#  define PATH_HEREDOC "/tmp/minishell_heredoc_tmp"
# endif

typedef struct s_env			t_env;
typedef struct s_token			t_token;
typedef struct s_ast_node		t_ast_node;

typedef struct s_shell
{
	t_strvector					*env;
	int							exit_status;
	char						*input;
	t_token						*tokens;
	t_ast_node					*ast;
	int							saved_fds[2];
	bool						is_interactive;
}								t_shell;

extern volatile sig_atomic_t	g_sig_status;

void							initialize_shell(t_shell *shell, char **envp);
void							exit_shell(t_shell *shell);
void							cleanup_shell(t_shell *shell);
void							close_shell_fds(t_shell *shell);
void							exit_shell_with_error(t_shell *shell,
									const char *message, int errnum);

/* signals */
void							sigint_handler(int sig);
void							sigint_heredoc_handler(int sig);
void							print_signal_error(int sig);

/* prints */
void							shell_perror(const char *msg);
void							shell_puterror(char *prefix, char *msg);
void							print_exit_status(t_shell *shell);

/* loop */
void							shell_loop_interactive(t_shell *shell);
void							shell_loop_non_interactive(t_shell *shell);

#endif
