/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:43:11 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/24 15:55:09 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/expander.h"

static char	*expand_heredoc_line(t_shell *shell, char *line)
{
	char	*expanded;

	expanded = expand_token_value(shell, line, true);
	if (!expanded)
	{
		free(line);
		shell->syserror = true;
		return (NULL);
	}
	free(line);
	return (expanded);
}

static void	heredoc_write(t_redirect *redirect, t_shell *shell, int fd)
{
	char	*line;

	while (true)
	{
		line = readline("\033[35m> \033[0m");
		if (!line)
			printf("minishell: %s (wanted `%s')\n", WARNING_HEREDOC,
				redirect->value);
		if (!line || ft_strcmp(line, redirect->value) == 0)
		{
			free(line);
			break ;
		}
		if (!redirect->quoted)
		{
			line = expand_heredoc_line(shell, line);
			if (!line)
				break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

char	*heredoc_get_path(void)
{
	char	*path;
	char	*numstr;
	int		i;

	i = 0;
	while (true)
	{
		path = NULL;
		numstr = ft_itoa(i++);
		if (!numstr)
			break ;
		path = ft_strjoin(PATH_HEREDOC, numstr);
		free(numstr);
		numstr = NULL;
		if (!path || access(path, F_OK) == -1)
			break ;
		free(path);
	}
	return (path);
}

void	heredoc_child(t_redirect *redirect, t_shell *shell, char *path)
{
	int	fd;

	shell->process_depth++;
	signal(SIGINT, SIG_DFL);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	free(path);
	path = NULL;
	if (fd == -1)
		exit_shell_with_error(shell, "failed to create heredoc file", 1);
	heredoc_write(redirect, shell, fd);
	close(fd);
	exit_shell(shell);
}

int	expand_heredoc(t_redirect *redirect, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = heredoc_get_path();
	if (!path)
		return (shell->syserror = true, -1);
	pid = fork();
	if (pid == -1)
		return (free(path), shell->syserror = true, -1);
	if (pid == 0)
		heredoc_child(redirect, shell, path);
	else
	{
		waitpid(pid, &status, 0);
		redirect->filename = path;
		if (WIFSIGNALED(status))
			return (shell->interrupted = true, 128 + WTERMSIG(status));
	}
	return (0);
}
