#ifndef MINISHELL_AST_H
# define MINISHELL_AST_H

typedef struct s_token	t_token;

typedef enum e_ast_type
{
    AST_COMMAND,
    AST_PIPE,
    AST_AND,
    AST_OR,
    AST_REDIRECT_IN,
    AST_REDIRECT_OUT,
    AST_APPEND,
    AST_HEREDOC,
}   t_ast_type;

typedef struct s_ast_node
{
    t_ast_type          type;
    char                **args;
    char                *filename;
    struct s_ast_node   *left;
    struct s_ast_node   *right;
}   t_ast_node;

t_ast_node  *parse_tokens(t_token *tokens);
t_ast_node  *create_ast_node(t_ast_type type);
void        free_ast(t_ast_node *node);
void        print_ast(t_ast_node *node, int depth);

#endif