/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 22:57:53 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 15:25:58 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_strvector	*env_init(char **envp)
{
	t_strvector	*env;
	size_t		i;
	size_t		size;

	if (!envp)
		return (NULL);
	size = 0;
	while (envp[size])
		size++;
	env = ft_sv_init(size + 10);
	if (!env)
		return (NULL);
	i = -1;
	while (++i < size)
		if (!ft_sv_push_back_dup(env, envp[i]))
		{
			ft_sv_free(env);
			return (NULL);
		}
	return (env);
}

bool	env_shlvl_increment(t_strvector *env)
{
	char	*shlvl_value;
	short	shlvl_int;
	char	*new_shlvl_str;

	shlvl_value = env_get_value("SHLVL", env);
	if (!shlvl_value)
		return (env_set(env, "SHLVL", "1"));
	shlvl_int = ft_atoi(shlvl_value);
	shlvl_int++;
	new_shlvl_str = ft_itoa(shlvl_int);
	if (!new_shlvl_str)
		return (false);
	if (!env_set(env, "SHLVL", new_shlvl_str))
	{
		free(new_shlvl_str);
		return (false);
	}
	free(new_shlvl_str);
	return (true);
}

void	print_env(t_strvector *env)
{
	size_t	i;

	if (!env)
		return ;
	i = 0;
	while (i < env->size)
	{
		printf("%s\n", env->data[i]);
		i++;
	}
}
