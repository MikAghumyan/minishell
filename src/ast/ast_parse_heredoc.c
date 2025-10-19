/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 01:33:46 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/19 15:01:22 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/env.h"
#include <wait.h>

static char	*heredoc_get_path(void)
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

static char	*expand_heredoc_line(t_parser *parser, char *line)
{
	char	*expanded;

	expanded = expand_token_value(parser->shell, line, true);
	if (!expanded)
	{
		free(line);
		parser->syserror = true;
		return (NULL);
	}
	free(line);
	return (expanded);
}

static void	heredoc_write(t_token *token, t_parser *parser, int fd)
{
	char	*line;

	while (true)
	{
		line = readline("\033[35m> \033[0m");
		if (!line && !g_sig_status)
			printf("minishell: %s (wanted `%s')\n", WARNING_HEREDOC,
				token->value);
		if (!line || ft_strcmp(line, token->value) == 0)
		{
			free(line);
			break ;
		}
		if (!token->quoted)
		{
			line = expand_heredoc_line(parser, line);
			if (!line)
				break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static void	heredoc_child(t_token *token, t_parser *parser, char *path)
{
	int	fd;

	signal(SIGINT, sigint_heredoc_handler);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(path);
		shell_perror("failed to create heredoc temp file");
		exit(1);
	}
	heredoc_write(token, parser, fd);
	close(fd);
	cleanup_shell(parser->shell);
	if (g_sig_status)
	{
		unlink(path);
		free(path);
		signal(SIGINT, SIG_DFL);
		kill(getpid(), g_sig_status);
	}
	free(path);
	if (parser->syserror)
		exit(1);
	exit(0);
}

char	*collect_heredoc(t_token *token, t_parser *parser)
{
	char	*path;
	pid_t	pid;
	int		status;

	path = heredoc_get_path();
	if (!path)
	{
		shell_perror("failed to generate heredoc temp file path");
		return (NULL);
	}
	pid = fork();
	if (pid == -1)
	{
		shell_perror("failed to fork heredoc process");
		return (free(path), NULL);
	}
	if (pid == 0)
		heredoc_child(token, parser, path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (free(path), NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (free(path), parser->interrupted = true, NULL);
	return (path);
}
