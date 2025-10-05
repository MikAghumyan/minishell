#include "../../includes/minishell.h"

char	*open_heredoc(t_token *redirect)
{
	int		fd;
	char	*line;

	if (!redirect || redirect->type != TOKEN_HEREDOC || !redirect->value)
		return (NULL);
	fd = open("/tmp/heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: failed to create heredoc temp file\n", 2);
		return (NULL);
	}
	while (true)
	{
		line = readline("heredoc> ");
		if (!line || (ft_strncmp(line, redirect->value,
					ft_strlen(redirect->value)) == 0))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	close(fd);
	return (ft_strdup("/tmp/heredoc_tmp"));
}

t_token	*attach_redirect_target(t_token *redirect)
{
	t_token	*temp;

	if (!redirect || !redirect->next)
		return (NULL);
	if (redirect->next->type == TOKEN_WORD)
	{
		free(redirect->value);
		if (redirect->type == TOKEN_HEREDOC)
			redirect->value = open_heredoc(redirect);
		else
			redirect->value = ft_strdup(redirect->next->value);
		if (!redirect->value)
		{
			ft_putstr_fd("minishell: memory allocation error\n", 2);
			return (NULL);
		}
		temp = redirect->next;
		redirect->next = temp->next;
		free(temp->value);
		free(temp);
	}
	return (redirect);
}
