/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:02 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/21 21:23:42 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include <stdio.h>

bool	env_keycmp(const char *key, const char *env_var)
{
	size_t	keylen;

	keylen = 0;
	while (key[keylen] && key[keylen] != '=')
		keylen++;
	return (!ft_strncmp(env_var, key, keylen) && env_var[keylen] == '=');
}

char	*env_generate_var(const char *key, const char *value)
{
	size_t	keylen;
	size_t	valuelen;
	char	*env_var;

	if (!key)
		return (NULL);
	keylen = ft_strlen(key);
	if (value)
		valuelen = ft_strlen(value);
	else
		valuelen = 0;
	env_var = malloc(keylen + valuelen + 2);
	if (!env_var)
		return (NULL);
	ft_memcpy(env_var, key, keylen);
	env_var[keylen] = '=';
	if (valuelen)
		ft_memcpy(env_var + keylen + 1, value, valuelen);
	env_var[keylen + 1 + valuelen] = '\0';
	return (env_var);
}

char	*env_get_value(const char *key, t_strvector *env)
{
	size_t	i;

	if (!key || !env)
		return (NULL);
	i = -1;
	while (++i < env->size)
	{
		if (env_keycmp(key, env->data[i]))
			return (env->data[i] + ft_strlen(key) + 1);
	}
	return (NULL);
}
