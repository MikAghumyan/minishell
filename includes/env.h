/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:07 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/08 22:25:52 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../libft/libft.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

typedef struct s_env
{
	char	**data;
	size_t	size;
	size_t	capacity;
}			t_env;

t_env		*env_init(char **envp);
void		env_free(t_env **env);
bool		env_set(t_env *env, const char *key, const char *value);
bool		env_keycmp(const char *key, const char *env_var);
char		*env_generate_var(const char *key, const char *value);
char		*env_get_value(const char *key, t_env *env);

#endif