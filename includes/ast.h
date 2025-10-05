#ifndef AST_H
# define AST_H

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
}						t_node_type;

typedef struct s_redirect
{
	t_node_type			type;
	char				*filename;
}						t_redirect;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	t_list				*redirect_files;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_parser
{
	t_token				*tokens;
	int					subshell_depth;
}						t_parser;

/* base ast functions */
t_ast_node				*build_ast(t_token *tokens);
t_ast_node				*create_ast_node(t_node_type type);
void					free_ast(t_ast_node *node);
void					print_ast(t_ast_node *node, int depth);

/* parsing functions */
t_ast_node				*ast_parse_logical(t_parser *parser);
t_ast_node				*ast_parse_pipeline(t_parser *parser);
t_ast_node				*ast_parse_simple_command(t_parser *parser);
t_ast_node				*ast_parse_redirections(t_parser *parser,
							t_ast_node *cmd_node);
/* parsing command*/
t_ast_node				*ast_parse_command(t_parser *parser);
t_ast_node				*ast_init_command(t_parser *parser);

/* parsing subshell*/
t_ast_node				*ast_parse_subshell(t_parser *parser);
t_ast_node				*ast_init_subshell(t_parser *parser);

/* collect arguments*/
char					**collect_ast_arguments(t_token *tokens);

/* redirect functions*/
t_list					*collect_ast_redirects(t_token *tokens);
t_list					*ast_init_redirect(t_token *token);
void					free_redirect(void *redirect_ptr);

/* utils */
int						is_subshell_ast_token(t_token *token);
int						is_redirect_ast_token(t_token *token);
int						is_logical_ast_token(t_token *token);
int						is_logicpipe_ast_token(t_token *token);
int						is_sub_lr_ast_token(t_token *token);

/* execute functions */
int						execute_ast(t_ast_node *node, t_shell *shell);
int						execute_command(t_ast_node *node, t_shell *shell);
int						execute_pipe(t_ast_node *node, t_shell *shell);
int						execute_logical(t_ast_node *node, t_shell *shell);
int						execute_subshell(t_ast_node *node, t_shell *shell);

/* path utils */
void					free_paths(char **paths);
char					**parse_path(char **envp);
char					*find_command_path(char *cmd, char **envp);

/*command execute utils*/
int						handle_command_not_found(t_ast_node *node,
							t_shell *shell);
void					handle_cmd_child(t_ast_node *node, char *cmd_path,
							t_shell *shell);
int						handle_cmd_parent(pid_t pid, char *command_path,
							t_shell *shell);
int						handle_command_exec_fork_error(char *command_path,
							t_shell *shell);
/* redirect handling */
int						handle_redirects(t_list *redirect_list);

/* pipe utils */
void					close_fds(int *pipefds);
int						close_fds_return_error(int *pipefds);
void					handle_left_pid(int *pipefds);
void					handle_right_pid(int *pipefds);
int						wait_for_children(pid_t left_pid, pid_t right_pid,
							t_shell *shell);
int						type_pipe_error_and_return(void);
pid_t					fork_left_child(t_ast_node *node, int *pipefds,
							t_shell *shell);
pid_t					fork_right_pid(t_ast_node *node, int *pipefds,
							t_shell *shell);

/* logical operator utils */
int						execute_and(t_ast_node *node, t_shell *shell);
int						execute_or(t_ast_node *node, t_shell *shell);

/*subshell utils*/
void					execute_subshell_in_child(t_ast_node *node,
							t_shell *shell);
int						wait_for_child(pid_t pid, t_shell *shell);
int						handle_subshell_fork_error(t_shell *shell);
#endif
