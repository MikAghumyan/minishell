#ifndef MINISHELL_TOKENIZER_H
# define MINISHELL_TOKENIZER_H

# include "../libft/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_INVALID,
	TOKEN_OR,
	TOKEN_AND,
}					e_token_type;

typedef struct s_token
{
	char			*value;
	e_token_type	type;
	struct s_token	*next;
}					t_token;

t_token				*tokenize_input(t_shell *shell);
void				free_tokens(t_token *tokens);
t_token				*add_operator_token(t_token **tokens, const char *value,
						size_t *i);
t_token				*add_token(t_token **tokens, const char *value,
						e_token_type type);
bool				is_operator(const char c);
void				print_tokens(t_token *tokens);

#endif