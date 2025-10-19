/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 19:00:23 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 15:08:50 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static bool	env_update_var(t_env *env, size_t i, const char *key,
		const char *value)
{
	free(env->data[i]);
	if (value)
		env->data[i] = env_generate_var(key, value);
	else
		env->data[i] = ft_strdup(key);
	if (!env->data[i])
		return (env_free(&env), false);
	return (true);
}

bool	env_set(t_env *env, const char *key, const char *value)
{
	size_t	i;

	if (!key)
		return (false);
	i = -1;
	while (env->data[++i])
		if (env_keycmp(key, env->data[i]))
			return (env_update_var(env, i, key, value));
	if (!env_check_capacity(env))
		return (env_free(&env), false);
	if (!env_update_var(env, env->size, key, value))
		return (false);
	env->size++;
	env->data[env->size] = NULL;
	return (true);
}

bool	env_unset(t_env *env, const char *key)
{
	size_t	i;
	size_t	j;

	if (!key)
		return (false);
	i = -1;
	while (env->data[++i])
	{
		if (env_keycmp(key, env->data[i]))
		{
			free(env->data[i]);
			j = i;
			while (j < env->size - 1)
			{
				env->data[j] = env->data[j + 1];
				j++;
			}
			env->data[env->size - 1] = NULL;
			env->size--;
			return (true);
		}
	}
	return (false);
}
