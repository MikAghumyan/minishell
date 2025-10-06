/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_char_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:53:21 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/07 01:15:09 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_chrop(char c)
{
	return (c == '|' || c == '&' || c == '(' || c == ')' || c == ';');
}

bool	is_chrredir(char c)
{
	return (c == '<' || c == '>');
}

bool	is_special_char(char c)
{
	return (is_chrop(c) || is_chrredir(c));
}

bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}