/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:36:47 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/08 22:54:39 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
// # include "env.h"
// # include "handlers.h"
// # include "tokenizer.h"
# include <errno.h>
// # include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
// # include <signal.h>
// # include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
// # include <sys/wait.h>
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

typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef struct s_ast_node	t_ast_node;

typedef struct s_shell
{
	t_env					*env;
	int						exit_status;
	char					*input;
	t_token					*tokens;
	t_ast_node				*ast;
}							t_shell;

void						initialize_shell(t_shell *shell, char **envp);
void						exit_shell(t_shell *shell);
void						cleanup_shell(t_shell *shell);
void						exit_shell_with_error(t_shell *shell,
								const char *message);

#endif
