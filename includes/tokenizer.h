#ifndef MINISHELL_TOKENIZER_H
# define MINISHELL_TOKENIZER_H

# include "../libft/libft.h"

struct t_shell;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_INVALID,
}					e_token_type;

typedef struct s_token
{
	char			*value;
	e_token_type	type;
	struct s_token	*next;
}					t_token;

t_token				*tokenize_input(t_shell *shell);
int					process_single_char(t_shell *shell, size_t *i,
						t_token **tokens);
size_t				scan_word(const char *input, size_t start,
						const char end_char);
int					add_redirect_token(t_token **tokens, const char *input,
						size_t *i);
int					add_operator_token(t_token **tokens, const char *input,
						size_t *i);
int					add_word_token(t_token **tokens, const char *input,
						size_t *i);
int					add_quote_token(t_token **tokens, const char *input,
						size_t *i);
int					add_token_slice(t_token **tokens, const char *start,
						size_t len, e_token_type type);
void				add_tokens_back(t_token **tokens, t_token *new_token);
void				free_tokens(t_token *tokens);
bool				is_operator(const char c);
void				print_tokens(t_token *tokens);

#endif