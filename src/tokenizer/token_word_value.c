/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:56:56 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/07 22:08:00 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	scan_word(const char *input, size_t start, const char end_char)
{
	size_t	end;

	if (!input || !input[start])
		return (start);
	end = start;
	if (end_char != ' ')
	{
		while (input[end] && input[end] != end_char)
			end++;
	}
	else
	{
		while (input[end] && !is_space(input[end]) && input[end] != '\''
			&& input[end] != '\"' && !is_special_char(input[end]))
			end++;
	}
	return (end);
}

static char	*add_word_slice(t_shell *shell, size_t *i)
{
	size_t	word_end;
	size_t	word_start;
	char	*word_slice;
	char	*expanded;

	if (!shell || !i)
		return (NULL);
	word_start = *i;
	word_end = scan_word(shell->input, *i, ' ');
	if (word_end == *i)
		return (NULL);
	*i = word_end;
	word_slice = ft_substr(shell->input, word_start, word_end - word_start);
	if (!word_slice)
		return (NULL);
	expanded = expand_token_value(shell, word_slice);
	free(word_slice);
	if (!expanded)
		return (NULL);
	return (expanded);
}

static char	*add_quote_slice(t_shell *shell, size_t *i, t_token_type *type)
{
	size_t	start;
	char	*word_slice;
	char	*expanded;

	if (!shell || !i || !type)
		return (NULL);
	start = ++(*i);
	*i = scan_word(shell->input, *i, shell->input[start - 1]);
	if (!shell->input[*i])
		*type = TOKEN_INVALID;
	word_slice = ft_substr(shell->input, start, *i - start);
	if (!word_slice)
		return (NULL);
	if (shell->input[*i] && shell->input[*i] == shell->input[start - 1])
		(*i)++;
	if (shell->input[start - 1] == '\"')
	{
		expanded = expand_token_value(shell, word_slice);
		free(word_slice);
		if (!expanded)
			return (NULL);
		word_slice = expanded;
	}
	return (word_slice);
}

static bool	process_token_part(t_shell *shell, size_t *i, char **value,
		t_token *token)
{
	char	*value_slice;
	char	*tmp;

	if (is_quote(shell->input[*i]))
	{
		token->quoted = true;
		value_slice = add_quote_slice(shell, i, &token->type);
	}
	else
		value_slice = add_word_slice(shell, i);
	if (!value_slice)
		return (false);
	if (!*value)
		*value = ft_strdup("");
	if (!*value)
		return (false);
	tmp = *value;
	*value = ft_strjoin(*value, value_slice);
	free(tmp);
	free(value_slice);
	if (!*value)
		return (false);
	return (true);
}

char	*get_word_value(t_shell *shell, size_t *i, t_token *token)
{
	char	*value;

	value = NULL;
	while (shell->input[*i] && shell->input[*i] != ' '
		&& !is_special_char(shell->input[*i]))
	{
		if (!process_token_part(shell, i, &value, token))
		{
			free(value);
			return (NULL);
		}
	}
	return (value);
}
