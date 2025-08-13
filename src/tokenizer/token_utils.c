#include "../../includes/minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

t_token	*add_token_slice(t_token **tokens, const char *start, size_t len,
		e_token_type type)
{
	t_token	*new_token;
	t_token	*last;

	if (!tokens || !start || len == 0)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (ft_putstr_fd("minishell: memory allocation failed\n", 2), NULL);
	new_token->value = ft_substr(start, 0, len);
	if (!new_token->value)
	{
		free(new_token);
		return (ft_putstr_fd("minishell: memory allocation failed\n", 2), NULL);
	}
	new_token->type = type;
	new_token->next = NULL;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
	return (new_token);
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
