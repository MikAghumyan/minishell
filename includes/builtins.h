/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 02:02:43 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 00:48:26 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "./env.h"
# include "./minishell.h"
# include <stdbool.h>
# include <sys/stat.h>
# include <unistd.h>

typedef			int(t_builtin_func)(const char **, t_shell *);

int				count_args(const char **argv);
t_builtin_func	*return_builtin_function(const char **argv);

int				test_builtin_function(const char **argv, t_shell *shell);
int				builtin_echo(const char **args, t_shell *shell);
int				builtin_exit(const char **args, t_shell *shell);
int				builtin_pwd(const char **args, t_shell *shell);
int				builtin_cd(const char **args, t_shell *shell);

#endif