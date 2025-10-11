/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:36:45 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 17:13:09 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	count_args(const char **argv)
{
	int	ac;

	ac = 0;
	if (!argv || !*argv)
		return (-1);
	while (argv[ac])
		ac++;
	return (ac);
}

t_builtin_func	*return_builtin_function(const char **argv)
{
	if (!argv || !argv[0])
		return (NULL);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (&builtin_echo);
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (&builtin_cd);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (&builtin_pwd);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (&builtin_export);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (&builtin_unset);
	else if (ft_strcmp(argv[0], "env") == 0)
		return (&builtin_env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (&builtin_exit);
	else
		return (NULL);
}
