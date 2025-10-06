#include "../../includes/ast.h"

static int	heredoc_loop(int pipefd[2], const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document \
delimited by end-of-file\n", 2);
			return (0);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			return (0);
		}
		if (write(pipefd[1], line, ft_strlen(line)) == -1
			|| write(pipefd[1], "\n", 1) == -1)
		{
			perror("write");
			free(line);
			return (-1);
		}
		free(line);
	}
}

int	handle_heredoc(t_redirect *redirect)
{
	int		pipefd[2];
	int		rc;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	rc = heredoc_loop(pipefd, redirect->filename);
	close(pipefd[1]);
	if (rc == -1)
		return (close(pipefd[0]), -1);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		return (close(pipefd[0]), perror("dup2"), -1);
	close(pipefd[0]);
	return (0);
}

int	handle_redirect_in(t_redirect *current, int *fd)
{
	*fd = open(current->filename, O_RDONLY);
	if (*fd == -1)
		return (perror(current->filename), -1);
	if (dup2(*fd, STDIN_FILENO) == -1)
		return (close(*fd), perror("dup2"), -1);
	close(*fd);
	return (0);
}

int	handle_redirect_out(t_redirect *current, int *fd)
{
	*fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
		return (perror(current->filename), -1);
	if (dup2(*fd, STDOUT_FILENO) == -1)
		return (close(*fd), perror("dup2"), -1);
	close(*fd);
	return (0);
}

int	handle_append(t_redirect *current, int *fd)
{
	*fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (perror(current->filename), -1);
	if (dup2(*fd, STDOUT_FILENO) == -1)
		return (close(*fd), perror("dup2"), -1);
	close(*fd);
	return (0);
}
