/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 22:57:53 by maghumya          #+#    #+#             */
/*   Updated: 2025/09/07 16:52:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	env_check_capacity(t_env *env)
{
	char	**new_data;
	size_t	i;

	if (env->size < env->capacity)
		return (true);
	env->capacity *= 2;
	new_data = (char **)malloc(sizeof(char *) * (env->capacity + 1));
	if (!new_data)
		return (false);
	i = -1;
	while (++i < env->size)
		new_data[i] = env->data[i];
	new_data[i] = NULL;
	free(env->data);
	env->data = new_data;
	return (true);
}
t_env	*env_init(char **envp)
{
	t_env	*env;
	size_t	i;

	if (!envp)
		return (NULL);
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->size = 0;
	while (envp[env->size])
		env->size++;
	env->capacity = env->size + 10;
	env->data = (char **)ft_calloc((env->capacity + 1), sizeof(char *));
	if (!env->data)
		return (free(env), NULL);
	i = -1;
	while (++i < env->size)
	{
		env->data[i] = ft_strdup(envp[i]);
		if (!env->data[i])
			return (env_free(&env), env);
	}
	env->data[i] = NULL;
	return (env);
}

bool	env_set(t_env *env, const char *key, const char *value)
{
	size_t	i;

	if (!key || !value)
		return (false);
	i = -1;
	while (env->data[++i])
	{
		if (env_keycmp(key, env->data[i]))
		{
			free(env->data[i]);
			env->data[i] = env_generate_var(key, value);
			if (!env->data[i])
				return (env_free(&env), false);
			return (true);
		}
	}
	if (!env_check_capacity(env))
		return (env_free(&env), false);
	env->data[env->size] = env_generate_var(key, value);
	if (!env->data[env->size])
		return (env_free(&env), false);
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
				env->data[j] = env->data[j + 1], j++;
			env->data[env->size - 1] = NULL;
			env->size--;
			return (true);
		}
	}
	return (false);
}
