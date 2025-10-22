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
			expand_heredoc(redirect, expander);
		else
			// status |= expand_redirection(current->content, expander);
			current = current->next;
	}
	return (status);
}

int	expand_heredoc(t_redirect *redirect, t_expander *expander)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		expander->syserror = true;
		return (-1);
	}
	if (pid == 0)
	{
	}
	return (0);
}