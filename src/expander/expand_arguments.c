/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:17:32 by maghumya          #+#    #+#             */
/*   Updated: 2025/11/01 14:30:41 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static int	expand_argument(char *arg, t_strvector **out, t_shell *shell)
{
	char	*expanded;
	char	*unquoted;

	expanded = expand_token_value(shell, arg, false);
	if (!expanded)
		return (shell->syserror = true, 1);
	unquoted = expand_quotes(expanded);
	free(expanded);
	if (!unquoted)
		return (shell->syserror = true, 1);
	if (!expand_wildcard(*out, unquoted))
	{
		free(unquoted);
		return (shell->syserror = true, 1);
	}
	free(unquoted);
	return (0);
}

int	expand_arguments(t_strvector **args, t_shell *shell)
{
	t_strvector	*newv;
	size_t		i;

	if (!args || !*args)
		return (0);
	newv = ft_sv_init((*args)->size);
	if (!newv)
		return (shell->syserror = true, 1);
	i = 0;
	while ((*args) && (*args)->data && (*args)->data[i])
	{
		if (expand_argument((*args)->data[i], &newv, shell))
			return (1);
		i++;
	}
	ft_sv_free(*args);
	*args = newv;
	return (0);
}
