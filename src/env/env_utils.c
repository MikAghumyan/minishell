/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:02 by maghumya          #+#    #+#             */
/*   Updated: 2025/08/23 15:39:03 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	env_keycmp(const char *key, const char *env_var)
{
	size_t	keylen;

	keylen = strlen(key);
	return (!ft_strncmp(env_var, key, keylen) && env_var[keylen] == '=');
}

char	*env_generate_var(const char *key, const char *value)
{
	size_t	keylen;
	size_t	valuelen;
	char	*env_var;

	keylen = strlen(key);
	valuelen = strlen(value);
	env_var = malloc(keylen + valuelen + 2);
	if (!env_var)
		return (NULL);
	memcpy(env_var, key, keylen);
	env_var[keylen] = '=';
	memcpy(env_var + keylen + 1, value, valuelen);
	env_var[keylen + 1 + valuelen] = '\0';
	return (env_var);
}

char	*env_get_value(const char *key, t_env *env)
{
	size_t	i;

	if (!key || !env)
		return (NULL);
	i = -1;
	while (++i < env->size)
	{
		if (env_keycmp(key, env->data[i]))
			return (env->data[i] + strlen(key) + 1);
	}
	return (NULL);
}

void	env_free(t_env **env)
{
	size_t	i;

	i = -1;
	if (!env || !*env)
		return ;
	if ((*env)->data)
		while (++i < (*env)->size)
		{
			free((*env)->data[i]);
			(*env)->data[i] = NULL;
		}
	free((*env)->data);
	(*env)->data = NULL;
	free(*env);
	*env = NULL;
}
