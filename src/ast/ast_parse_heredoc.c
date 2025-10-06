#include "../../includes/ast.h"
#include "../../includes/minishell.h"

static void	heredoc_write(char *delimiter, int fd)
{
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	*collect_heredoc(char *delimiter, t_parser *parser)
{
	char	*heredoc;
	int		fd;

	fd = open("/tmp/minishell_heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: failed to create heredoc temp file\n", 2);
		return (parser->syserror = true, NULL);
	}
	heredoc_write(delimiter, fd);
	close(fd);
	heredoc = ft_strdup("/tmp/minishell_heredoc_tmp");
	return (heredoc);
}
