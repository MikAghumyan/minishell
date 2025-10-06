#include "../../includes/ast.h"
#include "../../includes/minishell.h"

static bool	is_unexpected_token(t_token *token)
{
	return (token && (token->type == TOKEN_INVALID
			|| is_sub_lr_ast_token(token)));
}

t_list	*collect_ast_redirects(t_token *tokens, t_parser *parser)
{
	t_list	*list;
	t_list	*redirect_node;

	list = NULL;
	while (tokens && !is_logicpipe_ast_token(tokens)
		&& !is_unexpected_token(tokens))
	{
		if (is_redirect_ast_token(tokens))
		{
			redirect_node = ast_init_redirect(tokens, parser);
			if (!redirect_node)
				return (ft_lstclear(&list, free_redirect), NULL);
			ft_lstadd_back(&list, redirect_node);
		}
		tokens = tokens->next;
	}
	return (list);
}

t_list	*ast_init_redirect(t_token *token, t_parser *parser)
{
	t_redirect	*redirect;
	t_list		*redirect_node;

	if (!token)
		return (NULL);
	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (parser->syserror = true, NULL);
	redirect->type = (t_node_type)(token->type - TOKEN_REDIRECT_IN
			+ NODE_REDIRECT_IN);
	if (redirect->type == NODE_HEREDOC)
		redirect->filename = collect_heredoc(token, parser);
	else
		redirect->filename = ft_strdup(token->value);
	if (!redirect->filename)
		return (free(redirect), parser->syserror = true, NULL);
	redirect_node = ft_lstnew(redirect);
	if (!redirect_node)
		return (free(redirect), parser->syserror = true, NULL);
	return (redirect_node);
}

void	free_redirect(void *redirect_ptr)
{
	t_redirect	*redirect;

	if (!redirect_ptr)
		return ;
	redirect = (t_redirect *)redirect_ptr;
	if (redirect->filename)
		free(redirect->filename);
	free(redirect);
}
