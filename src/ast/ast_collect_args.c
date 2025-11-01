/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_collect_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:36:58 by maghumya          #+#    #+#             */
/*   Updated: 2025/11/02 00:36:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID
			|| is_sub_lr_ast_token(token)));
}

static bool	handle_fill_error(t_strvector **args, char *to_free,
		t_parser *parser)
{
	if (to_free)
		free(to_free);
	ft_sv_free(*args);
	parser->shell->syserror = true;
	return (false);
}

static bool	fill_args(t_strvector **args, t_token *tokens, t_parser *parser)
{
	while (tokens && !is_logicpipe_ast_token(tokens)
		&& !is_unexpected_token(tokens))
	{
		if (tokens->type == TOKEN_WORD)
		{
			if (!ft_sv_push_back_dup(*args, tokens->value))
				return (handle_fill_error(args, NULL, parser));
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
		parser->shell->syserror = true;
		return (NULL);
	}
	if (!fill_args(&args, tokens, parser))
		return (NULL);
	return (args);
}
