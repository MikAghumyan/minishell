/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_collect_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:36:58 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/20 16:47:15 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID
			|| is_sub_lr_ast_token(token)));
}

static size_t	count_token_args(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens && !is_logicpipe_ast_token(tokens)
		&& !is_unexpected_token(tokens))
	{
		if (tokens->type == TOKEN_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static bool	fill_args(t_strvector **args, t_token *tokens, t_parser *parser)
{
	char	*expanded_arg;

	while (tokens && !is_logicpipe_ast_token(tokens)
		&& !is_unexpected_token(tokens))
	{
		if (tokens->type == TOKEN_WORD)
		{
			expanded_arg = expand_token_value(parser->shell, tokens->value,
					false);
			if (!expanded_arg || ft_sv_push_back(*args, expanded_arg) == -1)
			{
				ft_sv_free(*args);
				parser->syserror = true;
				return (false);
			}
		}
		tokens = tokens->next;
	}
	return (true);
}

t_strvector	*collect_ast_arguments(t_token *tokens, t_parser *parser)
{
	size_t		count;
	t_strvector	*args;

	count = count_token_args(tokens);
	if (count == 0)
		return (NULL);
	args = ft_sv_init(count);
	if (!args)
	{
		parser->syserror = true;
		return (NULL);
	}
	if (!fill_args(&args, tokens, parser))
		return (NULL);
	return (args);
}
