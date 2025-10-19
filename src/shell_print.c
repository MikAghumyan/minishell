/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:58:14 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 13:55:48 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_perror(const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(msg);
}

void	shell_puterror(char *prefix, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (prefix)
	{
		ft_putstr_fd(prefix, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd((char *)msg, STDERR_FILENO);
}

void	print_exit_status(t_shell *shell)
{
	if (shell->exit_status != 0)
		printf("%sExit status: %d%s\n", RED, shell->exit_status, RESET);
	else
		printf("%sExit status: %d%s\n", GREEN, shell->exit_status, RESET);
}
