#include "../../includes/ast.h"

void	free_redirect_unlink(void *redirect_ptr)
{
	t_redirect	*redirect;

	if (!redirect_ptr)
		return ;
	redirect = (t_redirect *)redirect_ptr;
	if (redirect->type == NODE_HEREDOC && redirect->filename)
		unlink(redirect->filename);
	if (redirect->value)
		free(redirect->value);
	if (redirect->filename)
		free(redirect->filename);
	free(redirect);
}

void	free_redirect(void *redirect_ptr)
{
	t_redirect *redirect;

	if (!redirect_ptr)
		return ;
	redirect = (t_redirect *)redirect_ptr;
	if (redirect->value)
		free(redirect->value);
	if (redirect->filename)
		free(redirect->filename);
	free(redirect);
}