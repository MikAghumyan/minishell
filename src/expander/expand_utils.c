/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:11:11 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/13 20:11:18 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

size_t	get_varlen(const char *var)
{
	size_t	i;

	i = 0;
	if (!var || !*var)
		return (0);
	var++;
	while (var[i] && !is_space(var[i]) && !is_quote(var[i]) && var[i] != '$'
		&& var[i] != '=' && !is_special_char(var[i]))
		i++;
	return (i);
}

char	*expand_strjoin_free(char *s1, char *s2)
{
	char	*tmp;
	char	*result;

	tmp = s1;
	result = ft_strjoin(s1, s2);
	free(tmp);
	return (result);
}

char	*initialize_expand(t_expand_data *data)
{
	data->result = ft_strdup("");
	if (!data->result)
		return (NULL);
	data->in_dquote = false;
	data->in_squote = false;
	return (data->result);
}
