/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:08:38 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 16:54:00 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	builtin_export(const char **args, t_shell *shell)
{
	size_t	i;
	char	*assign;
	char	*key;
	char	*value;

	i = 1;
	if (!args[i])
		return (builtin_env(args, shell));
	shell->exit_status = 0;
	while (args[i])
	{
		assign = ft_strchr(args[i], '=');
		if (assign == NULL)
			return (0);
		if (assign - args[i] == 0)
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", args[i]);
			shell->exit_status = 1;
			i++;
			continue ;
		}
		key = ft_substr(args[i], 0, assign - args[i]);
		if (!key)
			exit_shell_with_error(shell, "minishell: export: system error", 1);
		value = assign + 1;
		if (!env_set(shell->env, key, value))
		{
			free(key);
			exit_shell_with_error(shell, "minishell: export: system error", 1);
		}
		free(key);
		i++;
	}
	return (shell->exit_status);
}
