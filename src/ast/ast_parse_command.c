/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:36:49 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/20 16:35:43 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID
			|| is_sub_lr_ast_token(token)));
}

t_ast_node	*ast_parse_command(t_parser *parser)
{
	t_ast_node	*result;

	if (!parser || !parser->tokens)
		return (NULL);
	if (is_subshell_ast_token(parser->tokens))
		return (ast_parse_subshell(parser));
	result = ast_init_command(parser);
	if (!result)
		return (NULL);
	while (parser->tokens && !is_logicpipe_ast_token(parser->tokens))
	{
		if (is_unexpected_token(parser->tokens))
		{
			if (parser->subshell_depth > 0
				&& parser->tokens->type == TOKEN_RPAREN)
				break ;
			free_ast(result);
			return (NULL);
		}
		parser->tokens = parser->tokens->next;
	}
	return (result);
}

t_ast_node	*ast_init_command(t_parser *parser)
{
	t_ast_node	*result;

	result = create_ast_node(NODE_COMMAND);
	if (!result)
		return (parser->syserror = true, NULL);
	result->type = NODE_COMMAND;
	result->args = collect_ast_arguments(parser->tokens, parser);
	result->redirect_files = collect_ast_redirects(parser->tokens, parser);
	if (parser->syserror || (!result->args && !result->redirect_files))
	{
		free_ast(result);
		return (NULL);
	}
	result->left = NULL;
	result->right = NULL;
	return (result);
}
