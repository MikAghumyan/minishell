/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:18:59 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 00:23:39 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	is_numeric(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
int	builtin_exit(const char **args, t_shell *shell)
{
	int	argc;

	argc = count_args(args);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	if (args[1])
	{
		if (!is_numeric(args[1]))
			exit_shell_with_error(shell,
				"minishell: exit: numeric argument required\n", STDERR_FILENO);
		shell->exit_status = (unsigned char)ft_atoi(args[1]);
	}
	exit_shell(shell);
	return (0);
}
