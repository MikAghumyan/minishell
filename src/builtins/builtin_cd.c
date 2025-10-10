#include "../../includes/builtins.h"

static const char	*set_newcwd(const char *arg, t_shell *shell)
{
	const char	*newcwd;

	if (!arg)
	{
		newcwd = env_get_value("HOME", shell->env);
		if (!newcwd)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
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
		perror("minishell: pwd");
		return (shell->exit_status = 1, 1);
	}
	else
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
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
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
