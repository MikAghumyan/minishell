/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:53:53 by maghumya          #+#    #+#             */
/*   Updated: 2025/11/01 19:31:19 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

t_token	*process_single_char(t_shell *shell, size_t *i, t_token **tokens)
{
	t_token	*token;

	token = NULL;
	if (is_chrop(shell->input[*i]))
		token = add_operator_token(tokens, shell, i);
	else if (is_chrredir(shell->input[*i]))
		token = add_redirect_token(tokens, shell, i);
	else
		token = add_word_token(shell, i, tokens);
	return (token);
}

t_token	*tokenize_input(t_shell *shell)
{
	size_t	i;
	t_token	*tokens;
	t_token	*new_token;

	if (!shell || !shell->input)
		return (NULL);
	i = 0;
	tokens = NULL;
	while (shell->input[i])
	{
		while (shell->input[i] && is_space(shell->input[i]))
			i++;
		if (!shell->input[i])
			break ;
		new_token = process_single_char(shell, &i, &tokens);
		if (!new_token)
		{
			shell->syserror = true;
			break ;
		}
	}
	return (tokens);
}
