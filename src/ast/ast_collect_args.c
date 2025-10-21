/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_collect_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:36:58 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/20 22:57:27 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID
			|| is_sub_lr_ast_token(token)));
}

static bool	handle_fill_error(t_strvector **args, char *expanded_arg,
		t_parser *parser)
{
	if (expanded_arg)
		free(expanded_arg);
	ft_sv_free(*args);
	parser->syserror = true;
	return (false);
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
			if (!expanded_arg)
				return (handle_fill_error(args, NULL, parser));
			if (!expand_wildcard(*args, expanded_arg))
				return (handle_fill_error(args, expanded_arg, parser));
			free(expanded_arg);
		}
		tokens = tokens->next;
	}
	return (true);
}

t_strvector	*collect_ast_arguments(t_token *tokens, t_parser *parser)
{
	t_strvector	*args;

	args = ft_sv_init(10);
	if (!args)
	{
		parser->syserror = true;
		return (NULL);
	}
	if (!fill_args(&args, tokens, parser))
		return (NULL);
	return (args);
}
