/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:33:09 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 01:21:34 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	builtin_echo(const char **args, t_shell *shell)
{
	size_t	i;
	bool	n_flag;
	int		argc;

	argc = count_args(args);
	i = 1;
	n_flag = false;
	while ((size_t)argc > i && ft_strcmp(args[i], "-n") == 0)
	{
		n_flag = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd((char *)args[i], STDOUT_FILENO);
		if (args[++i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	shell->exit_status = 0;
	return (shell->exit_status);
}
