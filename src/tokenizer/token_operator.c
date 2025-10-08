/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:53:29 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/08 21:55:49 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

static t_token_type	get_operator_type(const char *input, size_t i)
{
	if (ft_strncmp(&input[i], "&&", 2) == 0)
		return (TOKEN_AND);
	if (ft_strncmp(&input[i], "||", 2) == 0)
		return (TOKEN_OR);
	if (input[i] == '|')
		return (TOKEN_PIPE);
	if (input[i] == '&' || input[i] == ';')
		return (TOKEN_INVALID);
	if (input[i] == '(')
		return (TOKEN_LPAREN);
	if (input[i] == ')')
		return (TOKEN_RPAREN);
	return (TOKEN_INVALID);
}

t_token	*add_operator_token(t_token **tokens, t_shell *shell, size_t *i)
{
	t_token_type	type;
	size_t			end;
	t_token			*new_token;

	if (!shell || !shell->input || !tokens || !i)
		return (NULL);
	type = get_operator_type(shell->input, *i);
	if (type == TOKEN_AND || type == TOKEN_OR)
		end = 2;
	else
		end = 1;
	*i += end;
	new_token = add_token_slice(tokens, type);
	if (!new_token)
		return (NULL);
	new_token->value = ft_substr(shell->input, *i - end, end);
	if (!new_token->value)
		return (NULL);
	add_tokens_back(tokens, new_token);
	return (new_token);
}
