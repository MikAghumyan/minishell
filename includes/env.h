/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:07 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/21 21:17:29 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../libft/libft.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

t_strvector	*env_init(char **envp);
void		env_free(t_strvector **env);
bool		env_shlvl_increment(t_strvector *env);
bool		env_set(t_strvector *env, const char *key, const char *value);
bool		env_append(t_strvector *env, const char *key, const char *value);
bool		env_unset(t_strvector *env, const char *key);
size_t		env_get_keylen(const char *var);
bool		env_keycmp(const char *key, const char *env_var);
char		*env_generate_var(const char *key, const char *value);
char		*env_get_value(const char *key, t_strvector *env);
void		print_env(t_strvector *env);

#endif