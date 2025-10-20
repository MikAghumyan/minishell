/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_collect_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:36:58 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/20 20:46:59 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID
			|| is_sub_lr_ast_token(token)));
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
			{
				ft_sv_free(*args);
				parser->syserror = true;
				return (false);
			}
			// expand_wildcard()
			if (ft_sv_push_back(*args, expanded_arg) == -1)
			{
				free(expanded_arg);
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
	t_strvector	*args;  //no count anymore

	args = ft_sv_init(10);
	if (!args)
	{
		parser->syserror = true;
		return (NULL);
	}
	if (!fill_args(&args, tokens, parser))
		return (NULL);
	if (ft_sv_size(args) == 0)
	{
		ft_sv_free(args);
		return (NULL);
	}
	return (args);
}
