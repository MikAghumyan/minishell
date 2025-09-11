/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:12:22 by maghumya          #+#    #+#             */
/*   Updated: 2025/09/11 12:01:30 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_varlen(const char *var)
{
	size_t	i;

	i = 0;
	if (!var || !*var)
		return (0);
	var++;
	while (var[i] && (var[i] != ' ' && var[i] != '\t' && var[i] != '\''
			&& var[i] != '$' && !token_is_operator(var[i])))
		i++;
	return (i);
}

static char	*make_new_value(const char *value, const char *replacement,
		size_t pos, size_t keylen)
{
	size_t	value_len;
	size_t	replacement_len;
	size_t	new_len;
	char	*new_value;

	if (!value)
		return (NULL);
	if (!replacement)
		replacement = "";
	value_len = ft_strlen(value);
	replacement_len = ft_strlen(replacement);
	new_len = value_len - keylen - 1 + replacement_len;
	new_value = malloc(new_len + 1);
	if (!new_value)
		return (NULL);
	ft_memmove(new_value, value, pos);
	ft_memmove(new_value + pos, replacement, replacement_len);
	ft_memmove(new_value + pos + replacement_len, value + pos + 1 + keylen,
		value_len - pos - keylen - 1);
	new_value[new_len] = '\0';
	return (new_value);
}

static char	*expand_variable(t_shell *shell, const char *value, size_t pos,
		size_t keylen)
{
	char	*key;
	char	*env_value;
	char	*new_value;

	key = ft_substr(value, pos + 1, keylen);
	if (!key)
		return (NULL);
	env_value = env_get_value(key, shell->env);
	new_value = make_new_value(value, env_value, pos, keylen);
	free(key);
	return (new_value);
}

static char	*process_expansion(t_shell *shell, char *expanded, size_t *i)
{
	size_t	varlen;
	char	*tmp;

	varlen = get_varlen(expanded + *i);
	if (varlen == 0)
		return (expanded);
	tmp = expand_variable(shell, expanded, *i, varlen);
	free(expanded);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*expand_token_value(t_shell *shell, const char *value)
{
	size_t	i;
	char	*expanded;
	char	*tmp;

	if (!value)
		return (NULL);
	expanded = ft_strdup(value);
	if (!expanded)
		return (NULL);
	i = 0;
	while (expanded && expanded[i])
	{
		if (expanded[i] == '$')
		{
			tmp = process_expansion(shell, expanded, &i);
			if (!tmp)
				return (NULL);
			expanded = tmp;
		}
		i++;
	}
	return (expanded);
}
