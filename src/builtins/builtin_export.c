/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:08:38 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 22:18:07 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	builtin_export(const char **args, t_shell *shell)
{
	size_t	i;
	char	*assign;

	if (!args[1])
		return (builtin_env(args, shell));
	shell->exit_status = 0;
	i = 0;
	while (args[++i])
	{
		assign = ft_strchr(args[i], '=');
		if (assign == NULL)
			continue ;
		if (assign == args[i])
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", args[i]);
			shell->exit_status = 1;
			continue ;
		}
		env_set(shell->env, args[i], NULL);
	}
	return (shell->exit_status);
}
