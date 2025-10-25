/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:28:39 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/25 19:13:10 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static void	expand_rest(t_expand_data *expanded, char *token, size_t *i)
{
	size_t	len;
	char	*rest;

	len = get_varlen(&token[*i]) + 1;
	if (!len)
		return ;
	rest = ft_substr(token, *i, len);
	if (!rest)
		return (free(expanded->result), expanded->result = NULL, (void)0);
	expanded->result = expand_strjoin_free(expanded->result, rest);
	free(rest);
	*i += len - 1;
}

static void	expand_variable_with_key(t_shell *shell, t_expand_data *expanded,
		char *token, size_t *i)
{
	char	*key;
	size_t	keylen;
	char	*value;

	keylen = get_varlen(&token[*i]);
	if (!keylen)
		expanded->result = expand_strjoin_free(expanded->result, "$");
	else
	{
		key = ft_substr(token, *i + 1, keylen);
		if (!key)
			return (free(expanded->result), expanded->result = NULL, (void)0);
		value = env_get_value(key, shell->env);
		free(key);
		if (value)
			expanded->result = expand_strjoin_free(expanded->result, value);
		*i += keylen;
	}
}

static void	expand_variable(t_shell *shell, t_expand_data *expanded,
		char *token, size_t *i)
{
	char	*value;

	if (token[*i + 1] && token[*i + 1] == '?')
	{
		value = ft_itoa(shell->exit_status);
		if (!value)
			return (free(expanded->result), expanded->result = NULL, (void)0);
		expanded->result = expand_strjoin_free(expanded->result, value);
		free(value);
		(*i)++;
		return ;
	}
	else
		expand_variable_with_key(shell, expanded, token, i);
}

char	*expand_quotes(char *value)
{
	t_expand_data	expanded;
	size_t			i;

	if (!initialize_expand(&expanded))
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' && !expanded.in_dquote)
			expanded.in_squote = !expanded.in_squote;
		else if (value[i] == '\"' && !expanded.in_squote)
			expanded.in_dquote = !expanded.in_dquote;
		else
			expand_rest(&expanded, value, &i);
		if (!expanded.result)
			return (NULL);
		i++;
	}
	return (expanded.result);
}

char	*expand_token_value(t_shell *shell, char *value, bool heredoc)
{
	t_expand_data	expanded;
	size_t			i;

	if (!initialize_expand(&expanded))
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' && !expanded.in_dquote)
			expanded.in_squote = !expanded.in_squote;
		else if (value[i] == '\"' && !expanded.in_squote)
			expanded.in_dquote = !expanded.in_dquote;
		if (value[i] == '*' && (!expanded.in_squote && !expanded.in_dquote))
			expanded.result = expand_strjoin_free(expanded.result,
					expanded.wcstr);
		else if (value[i] == '$' && (!expanded.in_squote || heredoc))
			expand_variable(shell, &expanded, value, &i);
		else
			expand_rest(&expanded, value, &i);
		if (!expanded.result)
			return (NULL);
		i++;
	}
	return (expanded.result);
}
