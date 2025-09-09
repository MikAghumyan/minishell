#include "../../includes/ast.h"

int execute_ast(t_ast_node *node, t_shell *shell)
{
    if (!node)
        return (0);
    if (node->type == NODE_COMMAND)
        return (execute_command(node, shell));
    else if (node->type == NODE_PIPE)
        return (execute_pipe(node, shell));
    else if (node->type == NODE_AND || node->type == NODE_OR)
        return (execute_logical(node, shell));
    /*else if (node->type >= NODE_REDIRECT_IN && node->type <= NODE_HEREDOC)
        return (execute_redirect(node, shell));
    else if (node->type == NODE_SUBSHELL)
        return (execute_subshell(node, shell)); */
    else
        return (1);
}

int execute_command(t_ast_node *node, t_shell *shell)
{
    pid_t   pid;
    int     status;
    char    *command_path;

    if (!node || !node->args || !node->args[0])
        return (1);
    
    //TODO : checking commands

    command_path = find_command_path(node->args[0], shell->env->data);
    if (!command_path)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(node->args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        shell->exit_status = 127;
        return (127);
    }
    pid = fork();
    if (pid == 0)
    {
        execve(command_path, node->args, shell->env->data);
        perror("execve failed");
        exit(127); //means that command was not found
    }
    else if (pid > 0)
    {
        free(command_path);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            shell->exit_status = WEXITSTATUS(status);
        return (shell->exit_status);
    }
    else
    {
        free(command_path);
        perror("fork failed");
        shell->exit_status = 1;
        return (1);
    }
}

int execute_pipe(t_ast_node *node, t_shell *shell)
{
    int     pipefds[2];
    pid_t   left_pid;
    pid_t   right_pid;

    if (!node || !node->left || !node->right) //if there is no right or left child pipe is incorrect
        return (1);
    if (pipe(pipefds) == -1)
        return (type_error_and_return());
    left_pid = fork();
    if (left_pid == 0)
    {
        handle_left_pid(pipefds);
        exit(execute_ast(node->left, shell)); //execute left command and exit with return code
    }
    else if (left_pid < 0)
        return (close_fds_return_error(pipefds));
    right_pid = fork();
    if (right_pid == 0)
    {
        handle_right_pid(pipefds);
        exit(execute_ast(node->right, shell));
    }
    else if (right_pid < 0)
        return (close_fds_return_error(pipefds));
    close_fds(pipefds);
    return (wait_for_children(left_pid, right_pid, shell));
}

int execute_logical(t_ast_node *node, t_shell *shell)
{
    if (!node || !node->left)
        return (1);

    if (node->type == NODE_AND)
        return execute_and(node, shell);
    else if (node->type == NODE_OR)
        return execute_or(node, shell);
    return 1;
}