/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:25:26 by maghumya          #+#    #+#             */
/*   Updated: 2025/09/14 01:10:16 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static inline bool	is_operator_type(t_token *token)
{
	return (token->type >= TOKEN_PIPE && token->type <= TOKEN_AND);
}

static inline bool	is_redir_type(t_token *token)
{
	return (token->type >= TOKEN_REDIRECT_IN && token->type <= TOKEN_HEREDOC);
}

static inline bool	analyze_parentheses(t_token *token,
		size_t *count_parentheses)
{
	if (token->type == TOKEN_LPAREN)
		count_parentheses[0]++;
	else if (token->type == TOKEN_RPAREN)
		count_parentheses[1]++;
	if (!token->next)
		return (true);
	if (token->type == TOKEN_LPAREN && token->next->type == TOKEN_RPAREN)
		return (false);
	else if (token->type == TOKEN_LPAREN && is_operator_type(token->next))
		return (false);
	else if (is_operator_type(token) && token->next->type == TOKEN_RPAREN)
		return (false);
	else if (token->type == TOKEN_RPAREN && token->next->type == TOKEN_LPAREN)
		return (false);
	else if (token->type == TOKEN_WORD && token->next->type == TOKEN_LPAREN)
		return (false);
	else if (token->type == TOKEN_RPAREN && token->next->type == TOKEN_WORD)
		return (false);
	return (true);
}

static inline bool	analyze_tokens_order(t_token *token,
		size_t *count_parentheses)
{
	if (!token)
		return (false);
	if ((is_operator_type(token) || is_redir_type(token)) && !token->next)
		return (false);
	else if (is_operator_type(token) && is_operator_type(token->next))
		return (false);
	else if (is_redir_type(token) && token->next->type != TOKEN_WORD)
		return (false);
	else if (!analyze_parentheses(token, count_parentheses))
		return (false);
	return (true);
}

bool	analyze_tokens(t_token *token)
{
	size_t	count_parentheses[2];

	count_parentheses[0] = 0;
	count_parentheses[1] = 0;
	if (!token)
		return (false);
	if (is_operator_type(token))
		return (false);
	while (token)
	{
		if (token->type == TOKEN_INVALID || !analyze_tokens_order(token,
				count_parentheses))
			return (false);
		token = token->next;
	}
	if (count_parentheses[0] != count_parentheses[1])
	{
		printf("minishell: syntax error: unmatched parentheses\n");
		return (false);
	}
	return (true);
}
