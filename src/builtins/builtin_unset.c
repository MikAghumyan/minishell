/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:08:38 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 17:14:49 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	builtin_unset(const char **args, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (args[++i])
		env_unset(shell->env, args[i]);
	return (shell->exit_status = 0);
}
