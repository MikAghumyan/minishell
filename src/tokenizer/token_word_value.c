/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:56:56 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 14:57:33 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

size_t	scan_word(const char *input, size_t start, t_token *token)
{
	size_t	end;
	bool	in_squote;
	bool	in_dquote;

	if (!input || !input[start])
		return (start);
	end = start;
	in_squote = false;
	in_dquote = false;
	while (input[end])
	{
		if (input[end] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (input[end] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (input[end] == ' ' && !in_squote && !in_dquote)
			break ;
		else if (is_special_char(input[end]) && !in_squote && !in_dquote)
			break ;
		end++;
	}
	if (in_squote || in_dquote)
		token->type = TOKEN_INVALID;
	return (end);
}

char	*get_word_value(t_shell *shell, size_t *i, t_token *token)
{
	char	*value;
	size_t	end;

	end = scan_word(shell->input, *i, token);
	if (*i == end)
		return (NULL);
	value = ft_substr(shell->input, *i, end - *i);
	if (!value)
		return (NULL);
	*i = end;
	return (value);
}
