/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:12:22 by maghumya          #+#    #+#             */
/*   Updated: 2025/08/27 23:04:43 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_varlen(char *var)
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

static char	*expand_make_new_token(t_token *token, char *value, size_t *i,
		size_t keylen)
{
	char	*new_token_value;
	size_t	value_len;
	size_t	new_token_len;
	size_t	token_len;

	if (!value)
		value = "";
	token_len = ft_strlen(token->value);
	value_len = ft_strlen(value);
	new_token_len = token_len - keylen - 1 + value_len;
	new_token_value = malloc(sizeof(char) * (new_token_len + 1));
	if (!new_token_value)
		return (NULL);
	ft_memmove(new_token_value, token->value, *i);
	ft_memmove(new_token_value + *i, value, value_len);
	ft_memmove(new_token_value + *i + value_len, token->value + *i + 1 + keylen,
		ft_strlen(token->value + *i + keylen));
	new_token_value[new_token_len] = 0;
	free(token->value);
	token->value = new_token_value;
	*i += value_len - 1;
	return (new_token_value);
}

static char	*expand_variable(t_shell *shell, t_token *token, size_t *i,
		size_t keylen)
{
	char	*new_token_value;
	char	*value;
	char	*key;

	key = ft_substr(token->value, *i + 1, keylen);
	if (!key)
		return (NULL);
	value = env_get_value(key, shell->env);
	free(key);
	key = NULL;
	if (!value)
		value = "";
	new_token_value = expand_make_new_token(token, value, i, keylen);
	if (!new_token_value)
		return (NULL);
	return (new_token_value);
}

char	*expand_token(t_shell *shell, t_token *token)
{
	size_t	i;
	size_t	varlen;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			varlen = get_varlen(token->value + i);
			if (varlen)
				if (!expand_variable(shell, token, &i, varlen))
					return (NULL);
		}
		i++;
	}
	return (token->value);
}
