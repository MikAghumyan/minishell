#include "../../includes/minishell.h"

bool	token_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
		|| c == ';');
}

t_token	*add_token_slice(t_token **tokens, const char *start, size_t len,
		e_token_type type)
{
	t_token	*new_token;

	if (!tokens || !start)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_substr(start, 0, len);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->next = NULL;
	add_tokens_back(tokens, new_token);
	return (new_token);
}

void	add_tokens_back(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	if (!tokens)
	{
		return ;
	}
	while (current)
	{
		printf("Token: '%s', Type: %d, Length: %zu\n",
			current->value ? current->value : "(null)", current->type,
			current->value ? ft_strlen(current->value) : 0);
		current = current->next;
		count++;
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
