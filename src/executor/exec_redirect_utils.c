/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahakya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:01:11 by nsahakya          #+#    #+#             */
/*   Updated: 2025/10/21 13:01:12 by nsahakya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	handle_redirect_in(t_redirect *current, int *fd)
{
	*fd = open(current->filename, O_RDONLY);
	if (*fd == -1)
	{
		shell_perror(current->filename);
		return (-1);
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		close(*fd);
		shell_perror("dup2");
		return (-1);
	}
	close(*fd);
	return (0);
}

int	handle_redirect_out(t_redirect *current, int *fd)
{
	*fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		shell_perror(current->filename);
		return (-1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
	{
		close(*fd);
		shell_perror("dup2");
		return (-1);
	}
	close(*fd);
	return (0);
}

int	handle_append(t_redirect *current, int *fd)
{
	*fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		shell_perror(current->filename);
		return (-1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
	{
		close(*fd);
		shell_perror("dup2");
		return (-1);
	}
	close(*fd);
	return (0);
}

int	handle_redirects(t_list *redirect_list)
{
	t_list		*current;
	t_redirect	*redirect;
	int			fd;
	int			result;

	if (!redirect_list)
		return (0);
	current = redirect_list;
	result = 0;
	while (current && result == 0)
	{
		redirect = (t_redirect *)current->content;
		if (redirect->type == NODE_REDIRECT_IN)
			result = handle_redirect_in(redirect, &fd);
		else if (redirect->type == NODE_REDIRECT_OUT)
			result = handle_redirect_out(redirect, &fd);
		else if (redirect->type == NODE_APPEND)
			result = handle_append(redirect, &fd);
		else if (redirect->type == NODE_HEREDOC)
			result = handle_redirect_in(redirect, &fd);
		current = current->next;
	}
	return (result);
}
