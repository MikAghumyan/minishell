/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:26:37 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/12 21:35:43 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "./env.h"
# include "./minishell.h"
# include "./tokenizer.h"
# include <stdbool.h>

typedef struct s_expand_data
{
	char	*result;
	bool	in_dquote;
	bool	in_squote;
}			t_expand_data;

char		*expand_token_value(t_shell *shell, char *value, bool heredoc);

size_t		get_varlen(const char *var);
char		*expand_strjoin_free(char *s1, char *s2);
char		*initialize_expand(t_expand_data *data);

#endif