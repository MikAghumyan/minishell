/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:08:38 by maghumya          #+#    #+#             */
/*   Updated: 2025/11/01 19:30:58 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static bool	is_invalid_identifier(const char *args)
{
	const char	*assign;

	assign = ft_strchr(args, '=');
	if (assign == args)
		return (true);
	if (!assign)
		assign = args + ft_strlen((char *)args);
	if (args[0] && !ft_isalpha(args[0]) && args[0] != '_')
		return (true);
	while (args && args < assign)
	{
		if (*args == '+' && *(args + 1) == '=')
			break ;
		if (!ft_isalnum(*args) && *args != '_')
			return (true);
		args++;
	}
	return (false);
}

static int	export_variable(const char *arg, t_shell *shell)
{
	char		*key;
	const char	*value;

	if (is_invalid_identifier(arg))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	if (!ft_strchr(arg, '='))
		return (0);
	key = ft_substr(arg, 0, env_get_keylen(arg));
	if (!key)
		return (1);
	value = ft_strchr(arg, '=') + 1;
	if (arg[ft_strlen(key)] == '+')
		env_append(shell->env, key, value);
	else
		env_set(shell->env, key, value);
	free(key);
	return (0);
}

int	builtin_export(const char **args, t_shell *shell)
{
	size_t	i;

	if (!args[1])
		return (builtin_env(args, shell));
	shell->exit_status = 0;
	i = 0;
	while (args[++i])
	{
		if (export_variable(args[i], shell))
			shell->exit_status = 1;
	}
	return (shell->exit_status);
}
