/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:53:47 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/06 20:45:46 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*add_word_token(t_shell *shell, size_t *i, t_token **tokens)
{
	t_token			*token;
	char			*value;
	t_token_type	type;

	token = NULL;
	type = TOKEN_WORD;
	value = get_word_value(shell, i, &type);
	if (value)
	{
		token = add_token_slice(tokens, type);
		if (!token)
			return (free(value), NULL);
		token->value = value;
		add_tokens_back(tokens, token);
	}
	return (token);
}
