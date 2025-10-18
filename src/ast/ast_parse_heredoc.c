/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 01:33:46 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/18 16:29:31 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/env.h"

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
		if (!line)
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
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	*collect_heredoc(t_token *token, t_parser *parser)
{
	char	*path;
	int		fd;

	path = heredoc_get_path();
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
