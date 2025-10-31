/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:57:52 by nsahakya          #+#    #+#             */
/*   Updated: 2025/10/24 00:04:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

t_ast_node	*build_ast(t_shell *shell)
{
	t_parser	parser;
	t_ast_node	*result;

	if (!shell->tokens)
		return (NULL);
	initialize_parser(&parser, shell, shell->tokens);
	result = ast_parse_logical(&parser);
	if (!result)
	{
		if (shell->syserror)
			exit_shell_with_error(shell, "system error", 1);
		if (parser.tokens)
			ft_fprintf(2,
				"minishell: syntax error near unexpected token `%s'\n",
				parser.tokens->value);
		else
			ft_fprintf(2, "minishell: syntax error: unexpected end of line\n");
		shell->exit_status = 2;
	}
	return (result);
}

void	initialize_parser(t_parser *parser, t_shell *shell, t_token *tokens)
{
	parser->tokens = tokens;
	parser->shell = shell;
	parser->subshell_depth = 0;
}

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirect_files = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	free_ast(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->args)
	{
		ft_sv_free(node->args);
		node->args = NULL;
	}
	if (node->redirect_files)
	{
		if (shell && shell->process_depth == 0)
			ft_lstclear(&node->redirect_files, free_redirect_unlink);
		else
			ft_lstclear(&node->redirect_files, free_redirect);
	}
	free_ast(node->right, shell);
	free_ast(node->left, shell);
	free(node);
}
