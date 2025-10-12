/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:49:32 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 16:06:44 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	builtin_env(const char **args, t_shell *shell)
{
	if (args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", STDERR_FILENO);
		return (shell->exit_status = 1);
	}
	else
	{
		if (shell->env)
			print_env(shell->env);
	}
	return (shell->exit_status = 0);
}
