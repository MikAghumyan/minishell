/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:23:00 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/25 19:15:55 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static int	expand_redirect_filename(t_redirect *redirect, t_shell *shell)
{
	char	*temp;

	temp = expand_token_value(shell, redirect->filename, false);
	if (!temp && shell->syserror)
		return (1);
	free(redirect->filename);
	redirect->filename = temp;
	temp = expand_quotes(redirect->filename);
	if (!temp && shell->syserror)
		return (1);
	free(redirect->filename);
	redirect->filename = temp;
	recover_pattern(redirect->filename);
	return (0);
}

static int	expand_heredoc_delimiter(t_redirect *redirect, t_shell *shell)
{
	char	*temp;

	temp = expand_quotes(redirect->value);
	if (!temp && shell->syserror)
		return (1);
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
		if (redirect->type == NODE_HEREDOC)
		{
			if (expand_heredoc_delimiter(redirect, shell))
				return (1);
			status = expand_heredoc(redirect, shell);
			if (status)
				return (status);
		}
		else if (expand_redirect_filename(redirect, shell))
			return (1);
		current = current->next;
	}
	return (status);
}
