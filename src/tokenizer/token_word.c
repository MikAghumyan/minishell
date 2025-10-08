/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:53:47 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/08 21:55:43 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

t_token	*add_word_token(t_shell *shell, size_t *i, t_token **tokens)
{
	t_token			*token;
	t_token_type	type;

	type = TOKEN_WORD;
	token = add_token_slice(tokens, type);
	if (!token)
		return (NULL);
	token->value = get_word_value(shell, i, token);
	if (!token->value)
		return (NULL);
	add_tokens_back(tokens, token);
	return (token);
}
