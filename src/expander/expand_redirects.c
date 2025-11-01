/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:23:00 by maghumya          #+#    #+#             */
/*   Updated: 2025/11/01 19:34:22 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static int	expand_redirect_filename(t_redirect *redirect, t_shell *shell)
{
	char	*temp;

	temp = expand_token_value(shell, redirect->filename, false);
	if (!temp)
		return (shell->syserror = true, 1);
	free(redirect->filename);
	redirect->filename = temp;
	temp = expand_quotes(redirect->filename);
	if (!temp)
		return (shell->syserror = true, 1);
	free(redirect->filename);
	redirect->filename = temp;
	recover_pattern(redirect->filename);
	return (0);
}

static int	expand_heredoc_delimiter(t_redirect *redirect, t_shell *shell)
{
	char	*temp;

	temp = expand_quotes(redirect->value);
	if (!temp)
		return (shell->syserror = true, 1);
	free(redirect->value);
	redirect->value = temp;
	return (0);
}

int	expand_redirections(t_list *redirects, t_shell *shell)
{
	t_list		*current;
	int			status;
	t_redirect	*redirect;

	current = redirects;
	status = 0;
	while (current)
	{
		redirect = (t_redirect *)current->content;
		if (redirect->type != NODE_HEREDOC)
			if (expand_redirect_filename(redirect, shell))
				return (1);
		current = current->next;
	}
	return (status);
}

int	process_ast_heredocs(t_ast_node *node, t_shell *shell)
{
	t_list		*current_redirect;
	t_redirect	*redirect;
	int			status;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND || node->type == NODE_SUBSHELL)
	{
		current_redirect = node->redirect_files;
		while (current_redirect)
		{
			redirect = (t_redirect *)current_redirect->content;
			if (redirect->type == NODE_HEREDOC)
			{
				if (expand_heredoc_delimiter(redirect, shell))
					return (1);
				status = expand_heredoc(redirect, shell);
				if (status)
					return (status);
			}
			current_redirect = current_redirect->next;
		}
	}
	return (process_ast_heredocs(node->left, shell)
		|| process_ast_heredocs(node->right, shell));
}
