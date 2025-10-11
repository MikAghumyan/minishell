/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:08:38 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 19:27:12 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	builtin_export(const char **args, t_shell *shell)
{
	size_t	i;
	char	*assign;

	i = 1;
	if (!args[i])
		return (builtin_env(args, shell));
	shell->exit_status = 0;
	while (args[i])
	{
		assign = ft_strchr(args[i], '=');
		if (assign == NULL)
			continue ;
		if (assign == args[i])
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", args[i]);
			shell->exit_status = 1;
			i++;
			continue ;
		}
		env_set(shell->env, args[i], NULL);
		i++;
	}
	return (shell->exit_status);
}
