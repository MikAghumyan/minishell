#include "../../includes/minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

t_token	*add_token(t_token **tokens, const char *value, e_token_type type)
{
	t_token	*new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
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
	t_token *current = tokens;
	while (current)
	{
		printf("Token: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
}