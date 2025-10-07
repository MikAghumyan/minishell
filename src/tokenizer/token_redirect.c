/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:57:26 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/07 21:57:27 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token_type	get_redir_type(const char *input, size_t *i, size_t *len)
{
	t_token_type	type;

	if (ft_strncmp(&input[*i], ">>", 2) == 0)
		type = TOKEN_APPEND;
	else if (ft_strncmp(&input[*i], "<<", 2) == 0)
		type = TOKEN_HEREDOC;
	else if (input[*i] == '<')
		type = TOKEN_REDIRECT_IN;
	else if (input[*i] == '>')
		type = TOKEN_REDIRECT_OUT;
	else
		type = TOKEN_INVALID;
	if (type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		*len = 2;
	else
		*len = 1;
	*i += *len;
	while (input[*i] && is_space(input[*i]))
		(*i)++;
	if (!input[*i] || is_special_char(input[*i]))
		type = TOKEN_INVALID;
	return (type);
}

t_token	*add_redirect_token(t_token **tokens, t_shell *shell, size_t *i)
{
	t_token_type	type;
	size_t			start;
	size_t			len;
	t_token			*new_token;

	if (!shell || !shell->input || !tokens || !i)
		return (NULL);
	start = *i;
	type = get_redir_type(shell->input, i, &len);
	new_token = add_token_slice(tokens, type);
	if (!new_token)
		return (NULL);
	if (new_token->type == TOKEN_INVALID)
		new_token->value = ft_substr(shell->input, start, len);
	else
		new_token->value = get_word_value(shell, i, new_token);
	if (!new_token->value)
		return (NULL);
	add_tokens_back(tokens, new_token);
	return (new_token);
}
