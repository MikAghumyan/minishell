#include "../../includes/ast.h"

int execute_ast(t_ast_node *node, t_shell *shell)
{
    if (!node)
        return (0);
    if (node->type == NODE_COMMAND)
        return (execute_command(node, shell));
   /* else if (node->type == NODE_PIPE)
        return (execute_pipe(node, shell));
    else if (node->type == NODE_AND || node->type == NODE_OR)
        return (execute_logical(node, shell));
    else if (node->type >= NODE_REDIRECT_IN && node->type <= NODE_HEREDOC)
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

    if (!node || !node->args || !node->args[0])
        return (1);
    
    //TODO : checking commands

    pid = fork();
    if (pid == 0)
    {
        execvp(node->args[0], node->args);
        ft_putstr_fd("command not found: ", 2);
        ft_putstr_fd(node->args[0], 2);
        ft_putstr_fd("\n", 2);
        exit(127); //means that command was not found
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            shell->exit_status = WEXITSTATUS(status);
        return (shell->exit_status);
    }
    else
    {
        perror("fork failed");
        return (1);
    }
}