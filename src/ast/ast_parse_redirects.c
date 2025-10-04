#include "../../includes/ast.h"
#include "../../includes/minishell.h"

t_list	*collect_ast_redirects(t_token *tokens)
{
	t_list	*list;
	t_list	*redirect_node;

	list = NULL;
	while (tokens && !is_logicpipe_ast_token(tokens))
	{
		if (is_redirect_ast_token(tokens))
		{
			redirect_node = ast_init_redirect(tokens);
			if (!redirect_node)
				return (ft_lstclear(&list, free_redirect), NULL);
			ft_lstadd_back(&list, redirect_node);
		}
		tokens = tokens->next;
	}
	return (list);
}

t_list	*ast_init_redirect(t_token *token)
{
	t_redirect	*redirect;
	t_list		*redirect_node;

	if (!token)
		return (NULL);
	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->type = (t_node_type)(token->type - TOKEN_REDIRECT_IN
			+ NODE_REDIRECT_IN);
	redirect->filename = ft_strdup(token->value);
	if (!redirect->filename)
	{
		free(redirect);
		return (NULL);
	}
	redirect_node = ft_lstnew(redirect);
	if (!redirect_node)
	{
		free_redirect(redirect);
		return (NULL);
	}
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
