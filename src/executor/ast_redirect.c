#include "../../includes/ast.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

// static int	handle_heredoc(t_redirect *redirect)
// {
// 	int		pipefd[2];
// 	char	*line;
// 	char	*delimiter;

// 	delimiter = redirect->filename; // The delimiter is stored in filename
// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("pipe");
// 		return (-1);
// 	}
// 	while (1) // Read lines until delimiter is found
// 	{
// 		line = readline("> ");
// 		if (!line) // EOF
// 		{
// 			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n",
// 				2);
// 			close(pipefd[1]);
// 			break ;
// 		}
// 		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
// 			&& ft_strlen(line) == ft_strlen(delimiter))
// 		{
// 			free(line);
// 			close(pipefd[1]);
// 			break ;
// 		}
// 		if (write(pipefd[1], line, ft_strlen(line)) == -1 || write(pipefd[1],
// 				"\n", 1) == -1)
// 		{
// 			perror("write");
// 			free(line);
// 			close(pipefd[1]);
// 			close(pipefd[0]);
// 			return (-1);
// 		}
// 		free(line);
// 	}
// 	close(pipefd[1]);                        // Close write end
// 	if (dup2(pipefd[0], STDIN_FILENO) == -1) // Redirect stdin to read from pipe
// 	{
// 		close(pipefd[0]);
// 		perror("dup2");
// 		return (-1);
// 	}
// 	close(pipefd[0]);
// 	return (0);
// }

int	handle_redirect_in(t_redirect *current, int *fd)
{
	*fd = open(current->filename, O_RDONLY);
	if (*fd == -1)
	{
		perror(current->filename); // open file for reading and dup STDIN fd
		return (-1);
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		close(*fd);
		perror("dup2");
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
		perror(current->filename);
		return (-1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
	// open file for both reading and writing and dup STDOUT fd
	{
		close(*fd);
		perror("dup2");
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
		perror(current->filename);
		return (-1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1) // open or create file and dup STDOUT
	{
		close(*fd);
		perror("dup2");
		return (-1);
	}
	close(*fd);
	return (0);
}

int	handle_redirects(t_list *redirect_list) // MAIN REDIRECT FUNC
{
	t_list *current;
	t_redirect *redirect;
	int fd;
	int result;

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
