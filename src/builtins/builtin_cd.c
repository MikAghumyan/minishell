/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 14:06:10 by maghumya          #+#    #+#             */
/*   Updated: 2025/11/02 00:23:16 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static const char	*set_newcwd(const char *arg, t_shell *shell)
{
	const char	*newcwd;

	if (!arg)
	{
		newcwd = env_get_value("HOME", shell->env);
		if (!newcwd)
		{
			shell_puterror("cd", "HOME not set");
			return (NULL);
		}
	}
	else
		newcwd = arg;
	return (newcwd);
}

static int	update_cwd_var(t_shell *shell)
{
	char	*newcwd;
	char	*oldcwd;

	oldcwd = env_get_value("PWD", shell->env);
	if (oldcwd)
		env_set(shell->env, "OLDPWD", oldcwd);
	newcwd = getcwd(NULL, 0);
	if (!newcwd)
	{
		shell_perror("cd: getcwd failed");
		return (shell->exit_status = 1, 1);
	}
	env_set(shell->env, "PWD", newcwd);
	free(newcwd);
	return (shell->exit_status = 0, 0);
}

int	builtin_cd(const char **args, t_shell *shell)
{
	const char	*newcwd;
	int			argc;

	argc = count_args(args);
	if (argc > 2)
	{
		shell_puterror("cd", "too many arguments");
		return (shell->exit_status = 1, 1);
	}
	newcwd = set_newcwd(args[1], shell);
	if (!newcwd)
		return (shell->exit_status = 1, 1);
	if (chdir(newcwd) == -1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", newcwd,
			strerror(errno));
		return (shell->exit_status = 1, 1);
	}
	return (update_cwd_var(shell));
}
