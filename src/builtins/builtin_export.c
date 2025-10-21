/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:08:38 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/21 21:17:10 by maghumya         ###   ########.fr       */
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

int	builtin_export(const char **args, t_shell *shell)
{
	size_t	i;
	int		is_invalid;
	char	*key;

	if (!args[1])
		return (builtin_env(args, shell));
	shell->exit_status = 0;
	i = 0;
	while (args[++i])
	{
		is_invalid = is_invalid_identifier(args[i]);
		if (is_invalid)
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", args[i]);
			shell->exit_status = 1;
		}
		if (is_invalid || !ft_strchr(args[i], '='))
			continue ;
		key = ft_substr(args[i], 0, env_get_keylen(args[i]));
		if (!key)
			break ;
		if (args[i][ft_strlen(key)] == '+')
			env_append(shell->env, key, ft_strchr(args[i], '=') + 1);
		else
			env_set(shell->env, key, ft_strchr(args[i], '=') + 1);
		free(key);
	}
	return (shell->exit_status);
}
