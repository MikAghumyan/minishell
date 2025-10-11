/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_collect_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:36:58 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/11 12:36:58 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID
			|| is_sub_lr_ast_token(token)));
}

static size_t	count_args(t_token *tokens)
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

static bool	fill_args(char **args, t_token *tokens, t_parser *parser)
{
	size_t	i;

	i = 0;
	while (tokens && !is_logicpipe_ast_token(tokens)
		&& !is_unexpected_token(tokens))
	{
		if (tokens->type == TOKEN_WORD)
		{
			args[i] = ft_strdup(tokens->value);
			if (!args[i])
			{
				ft_free_array((void ***)&args);
				parser->syserror = true;
				return (false);
			}
			i++;
		}
		tokens = tokens->next;
	}
	return (true);
}

char	**collect_ast_arguments(t_token *tokens, t_parser *parser)
{
	size_t	count;
	char	**args;

	count = count_args(tokens);
	if (count == 0)
		return (NULL);
	args = ft_calloc(sizeof(char *), (count + 1));
	if (!args)
	{
		parser->syserror = true;
		return (NULL);
	}
	args[count] = NULL;
	if (!args)
		return (NULL);
	if (!fill_args(args, tokens, parser))
		return (NULL);
	return (args);
}
