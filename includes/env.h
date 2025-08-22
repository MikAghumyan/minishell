#ifndef ENV_H
# define ENV_H

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

#endif