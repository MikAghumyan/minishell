#include "../../includes/ast.h"

int	handle_redirects(t_redirect *redirect_list)
{
	t_redirect	*current;
	int			fd;
	int			result;

	if (!redirect_list)
		return (0);
	current = redirect_list;
	result = 0;
	while (current && result == 0)
	{
		if (current->type == NODE_REDIRECT_IN)
			result = handle_redirect_in(current, &fd);
		else if (current->type == NODE_REDIRECT_OUT)
			result = handle_redirect_out(current, &fd);
		else if (current->type == NODE_APPEND)
			result = handle_append(current, &fd);
		else if (current->type == NODE_HEREDOC)
			result = handle_heredoc(current);
		current = current->next;
	}
	return (result);
}
