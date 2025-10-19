/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 22:57:53 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 15:03:49 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

bool	env_check_capacity(t_env *env)
{
	char	**new_data;
	size_t	i;

	if (env->size < env->capacity)
		return (true);
	env->capacity *= 2;
	new_data = (char **)ft_calloc(sizeof(char *), (env->capacity + 1));
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
