/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 19:00:23 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/21 21:15:18 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

size_t	env_get_keylen(const char *key)
{
	size_t	len;

	len = 0;
	while (key[len] && (ft_isalnum(key[len]) || key[len] == '_'))
		len++;
	return (len);
}

bool	env_set(t_strvector *env, const char *key, const char *value)
{
	size_t	i;
	char	*new_var;

	if (!key || !value)
		return (false);
	i = -1;
	while (env->data[++i])
		if (env_keycmp(key, env->data[i]))
		{
			free(env->data[i]);
			env->data[i] = env_generate_var(key, value);
			if (!env->data[i])
				return (false);
		}
	new_var = env_generate_var(key, value);
	if (!new_var)
		return (false);
	if (!ft_sv_push_back(env, new_var))
		return (free(new_var), false);
	return (true);
}

bool	env_append(t_strvector *env, const char *key, const char *value)
{
	size_t	i;
	char	*current_value;
	char	*new_value;
	bool	res;

	if (!key || !value)
		return (false);
	i = -1;
	while (env->data[++i])
	{
		if (env_keycmp(key, env->data[i]))
		{
			current_value = env_get_value(key, env);
			if (!current_value)
				return (false);
			new_value = ft_strjoin(current_value, value);
			if (!new_value)
				return (false);
			res = env_set(env, key, new_value);
			free(new_value);
			return (res);
		}
	}
	return (env_set(env, key, value));
}

bool	env_unset(t_strvector *env, const char *key)
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
