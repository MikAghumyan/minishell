#include "../../includes/ast.h"
#include "../../includes/expander.h"

int	expand_redirections(t_list *redirects, t_expander *expander)
{
	t_list		*current;
	int			status;
	t_redirect	*redirect;

	current = redirects;
	status = 0;
	while (current)
	{
		redirect = (t_redirect *)current->content;
		if (redirect->type == NODE_HEREDOC)
			status = expand_heredoc(redirect, expander);
		// status |= expand_redirection(current->content, expander);
		current = current->next;
	}
	return (status);
}
