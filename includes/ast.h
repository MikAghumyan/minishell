/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:26:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/20 11:23:58 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../libft/libft.h"
# include "./expander.h"
# include "./minishell.h"
# include "./tokenizer.h"
# include <stdbool.h>

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

typedef enum e_dup_type
{
	DUP_IN,
	DUP_OUT,
}						t_dup_type;

typedef struct s_redirect
{
	t_node_type			type;
	char				*filename;
}						t_redirect;

typedef struct s_ast_node
{
	t_node_type			type;
	t_strvector			*args;
	t_list				*redirect_files;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_parser
{
	t_token				*tokens;
	t_shell				*shell;
	int					subshell_depth;
	bool				syserror;
	bool				interrupted;
}						t_parser;

/* base ast functions */
t_ast_node				*build_ast(t_shell *shell);
t_ast_node				*create_ast_node(t_node_type type);
void					initialize_parser(t_parser *parser, t_shell *shell,
							t_token *tokens);
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
t_strvector				*collect_ast_arguments(t_token *tokens,
							t_parser *parser);

/* redirect functions*/
t_list					*collect_ast_redirects(t_token *tokens,
							t_parser *parser);
t_list					*ast_init_redirect(t_token *token, t_parser *parser);
char					*collect_heredoc(t_token *token, t_parser *parser);
void					free_redirect(void *redirect_ptr);

/* utils */
int						is_subshell_ast_token(t_token *token);
int						is_redirect_ast_token(t_token *token);
int						is_logical_ast_token(t_token *token);
int						is_logicpipe_ast_token(t_token *token);
int						is_sub_lr_ast_token(t_token *token);

#endif
