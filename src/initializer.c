/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:38:55 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/06 17:35:34 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->env = env_init(envp);
	if (!shell->env)
	{
		perror("minishell: system error");
		exit(EXIT_FAILURE);
	}
	shell->input = NULL;
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->exit_status = 0;
}