/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:36:47 by maghumya          #+#    #+#             */
/*   Updated: 2025/09/14 00:15:07 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "handlers.h"
# include "tokenizer.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <wait.h>

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

typedef struct s_env	t_env;
typedef struct s_token	t_token;

typedef struct s_shell
{
	t_env				*env;
	int					exit_status;
	char				*input;
	t_token				*tokens;
}						t_shell;

# include "env.h"
# include "handlers.h"
# include "tokenizer.h"

void					initialize_shell(t_shell *shell, char **envp);

#endif
