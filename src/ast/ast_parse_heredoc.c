/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 01:33:46 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/12 21:41:11 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/env.h"

static char	*heredoc_get_path_base(t_env *env)
{
	if (access("/tmp/", R_OK | W_OK) == 0)
		return (ft_strdup("/tmp/minishell_heredoc_tmp"));
	if (access(env_get_value("HOME", env), F_OK | R_OK | W_OK) == 0)
		return (ft_strjoin(env_get_value("HOME", env),
				"/.minishell_heredoc_tmp"));
	else
		return (NULL);
}

static char	*heredoc_get_path(t_env *env)
{
	char	*path;
	char	*path_base;
	char	*numstr;
	int		i;

	i = 0;
	path_base = heredoc_get_path_base(env);
	if (!path_base)
		return (NULL);
	while (true)
	{
		path = NULL;
		numstr = ft_itoa(i++);
		if (!numstr)
			break ;
		path = ft_strjoin("/tmp/minishell_heredoc_tmp", numstr);
		free(numstr);
		numstr = NULL;
		if (!path)
			break ;
		if (access(path, F_OK) == -1)
			break ;
		free(path);
	}
	return (free(path_base), path);
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
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, token->value) == 0)
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
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	*collect_heredoc(t_token *token, t_parser *parser)
{
	char	*path;
	int		fd;

	path = heredoc_get_path(parser->shell->env);
	if (!path)
	{
		perror("minishell: failed to create heredoc temp file");
		return (parser->syserror = true, NULL);
	}
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(path);
		perror("minishell: failed to create heredoc temp file");
		return (parser->syserror = true, NULL);
	}
	heredoc_write(token, parser, fd);
	close(fd);
	return (path);
}
