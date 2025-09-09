#ifndef MINISHELL_AST_H
# define MINISHELL_AST_H

# include "minishell.h"
# include "tokenizer.h"

typedef enum e_node_type
{
    NODE_COMMAND,
    NODE_PIPE,
    NODE_AND,
    NODE_OR,
    NODE_REDIRECT_IN,
    NODE_REDIRECT_OUT,
    NODE_APPEND,
    NODE_HEREDOC,
    NODE_SUBSHELL,
}	e_node_type;

typedef struct s_ast_node
{
    e_node_type         type;
    char                **args;
    char                *redirect_file;
    struct s_ast_node   *left;
    struct s_ast_node   *right;
}   t_ast_node;

t_ast_node  *build_ast(t_token *tokens);
t_ast_node  *create_ast_node(e_node_type type);
void        free_ast(t_ast_node *node);
void        print_ast(t_ast_node *node, int depth);

t_ast_node  *ast_parse_logical(t_token **tokens);
t_ast_node  *ast_parse_pipeline(t_token **tokens);
t_ast_node  *ast_parse_command(t_token **tokens); // commands and redirects

//utils
int  is_subshell_ast_token(t_token *token);
int  is_redirect_ast_token(t_token *token);
int  is_logical_ast_token(t_token *token);
char  **collect_ast_arguments(t_token **tokens, int *arg_count);
t_ast_node  *ast_parse_simple_command(t_token **tokens);
t_ast_node  *create_redirect_ast_node(t_token *token);
t_ast_node  *ast_parse_redirections(t_token **tokens, t_ast_node *cmd_node);

//execute functions
int execute_ast(t_ast_node *node, t_shell *shell);
int execute_command(t_ast_node *node, t_shell *shell);
int execute_pipe(t_ast_node *node, t_shell *shell);
int execute_logical(t_ast_node *node, t_shell *shell);

//path utils
void    free_paths(char **paths);
char    **parse_path(char **envp);
char    *find_command_path(char *cmd, char **envp);

//pipe utils
void    close_fds(int *pipefds);
int     close_fds_return_error(int *pipefds);
void    handle_left_pid(int *pipefds);
void    handle_right_pid(int *pipefds);
int     wait_for_children(pid_t left_pid, pid_t right_pid, t_shell *shell);
int     type_error_and_return(void);

//logical utils
int execute_and(t_ast_node *node, t_shell *shell);
int execute_or(t_ast_node *node, t_shell *shell);

#endif