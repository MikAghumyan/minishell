/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 01:33:46 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/08 22:24:14 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

static char	*expand_heredoc_line(t_parser *parser, char *line)
{
	char	*expanded;

	expanded = expand_token_value(parser->shell, line);
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
	char	*heredoc;
	int		fd;

	fd = open("/tmp/minishell_heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: failed to create heredoc temp file\n", 2);
		return (parser->syserror = true, NULL);
	}
	heredoc_write(token, parser, fd);
	close(fd);
	heredoc = ft_strdup("/tmp/minishell_heredoc_tmp");
	return (heredoc);
}
