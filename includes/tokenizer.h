#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"
# include "./env.h"
# include "./minishell.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct s_shell	t_shell;

typedef enum e_token_type
{
	TOKEN_INVALID,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	bool				quoted;
	struct s_token		*next;
}						t_token;

/* TOKENIZER */
t_token					*tokenize_input(t_shell *shell);
t_token					*add_word_token(t_shell *shell, size_t *i,
							t_token **tokens);
t_token					*add_redirect_token(t_token **tokens, t_shell *shell,
							size_t *i);
t_token					*add_operator_token(t_token **tokens, t_shell *shell,
							size_t *i);

/* EXPANDER*/
char					*expand_token_value(t_shell *shell, const char *value);

/* TOKEN UTILS*/
void					add_tokens_back(t_token **tokens, t_token *new_token);
void					print_tokens(t_token *tokens);
void					free_tokens(t_token *tokens);
t_token					*add_token_slice(t_token **tokens, t_token_type type);

/* WORD UTILS*/
size_t					scan_word(const char *input, size_t start,
							const char end_char);
char					*get_word_value(t_shell *shell, size_t *i,
							t_token *new_token);

/* CHAR UTILS*/
bool					is_chrop(char c);
bool					is_chrredir(char c);
bool					is_special_char(char c);
bool					is_space(char c);
bool					is_quote(char c);

#endif