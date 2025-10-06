/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:53:40 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/06 22:37:52 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*add_token_slice(t_token **tokens, t_token_type type)
{
	t_token	*new_token;

	if (!tokens)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = NULL;
	new_token->type = type;
	new_token->quoted = false;
	new_token->next = NULL;
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
		printf("Token: '%s', Type: %d, Length: %zu, Quoted: %d\n",
			current->value ? current->value : "(null)", current->type,
			current->value ? ft_strlen(current->value) : 0, current->quoted);
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
