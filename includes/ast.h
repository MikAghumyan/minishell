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
    e_node_type         type;    // token type
    char                **args;  // command args
    char                *redirect_file; // redirection file
    struct s_ast_node   *left;
    struct s_ast_node   *right;
}   t_ast_node;

t_ast_node  *build_ast(t_token *tokens);
t_ast_node  *create_node(e_node_type type);
void        free_ast(t_ast_node *node);
void        print_ast(t_ast_node *node, int depth);

t_ast_node  *parse_logical(t_token **tokens); //&& ||
t_ast_node  *parse_pipeline(t_token **tokens); // |
t_ast_node  *parse_command(t_token **tokens); // commands and redirects

#endif