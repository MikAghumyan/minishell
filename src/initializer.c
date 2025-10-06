/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:38:55 by maghumya          #+#    #+#             */
/*   Updated: 2025/08/29 14:49:40 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->env = env_init(envp);
	// TODO handle error
	shell->input = NULL;
	shell->tokens = NULL;
	shell->exit_status = 0;
}