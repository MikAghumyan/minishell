#include "../../includes/ast.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static int handle_heredoc(t_redirect *redirect)
{
    int pipefd[2];
    char *line;
    char *delimiter;
    
    delimiter = redirect->filename; // The delimiter is stored in filename
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    while (1)  // Read lines until delimiter is found
    {
        line = readline("> ");
        if (!line) // EOF
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", 2);
            break;
        }
        if (strcmp(line, delimiter) == 0) //change to ft_strcmp in libft is only ft_strncmp
        {
            free(line);
            break;
        }
        write(pipefd[1], line, ft_strlen(line)); // Write line to pipe
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]); // Close write end
    if (dup2(pipefd[0], STDIN_FILENO) == -1) // Redirect stdin to read from pipe 
    {
        close(pipefd[0]);
        perror("dup2");
        return (-1);
    }
    close(pipefd[0]);
    return (0);
}

static int handle_redirect_in(t_redirect *current, int *fd)
{
    *fd = open(current->filename, O_RDONLY);
    if (*fd == -1)
    {
        perror(current->filename); //open file for reading and dup STDIN fd
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

static int  handle_redirect_out(t_redirect *current, int *fd)
{
    *fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*fd == -1)
    {
        perror(current->filename);
        return (-1);
    }
    if (dup2(*fd, STDOUT_FILENO) == -1)  //open file for both reading and writing and dup STDOUT fd
    {
        close(*fd);
        perror("dup2");
        return (-1);
    }
    close(*fd);
    return (0);
}

static int  handle_append(t_redirect *current, int *fd)
{
    *fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (*fd == -1)
    {
        perror(current->filename);
        return (-1);
    }
    if (dup2(*fd, STDOUT_FILENO) == -1)  //open or create file and dup STDOUT
    {
        close(*fd);
        perror("dup2");
        return (-1);
    }
    close(*fd);
    return (0);
}

int handle_redirects(t_redirect *redirect_list)  //MAIN REDIRECT FUNC
{
    t_redirect *current;
    int fd;

    current = redirect_list;
    while (current)
    {
        if (current->type == NODE_REDIRECT_IN)
        {
            if (handle_redirect_in(current, &fd) == -1)
                return (-1);
        }
        else if (current->type == NODE_REDIRECT_OUT)
        {
            if (handle_redirect_out(current, &fd) == -1)
                return (-1);
        }
        else if (current->type == NODE_APPEND)
        {
            if (handle_append(current, &fd) == -1)
                return (-1);
        }
        else if (current->type == NODE_HEREDOC)
        {
            if (handle_heredoc(current) == -1)
                return (-1);
        }
        current = current->next;
    }
    return (0);
}