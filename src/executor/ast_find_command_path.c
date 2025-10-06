#include "../../includes/ast.h"

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**parse_path(char **envp)
{
	char	*path;
	char	**paths;

	if (!envp || !*envp)
		return (NULL);
	path = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = *envp + 5;
			break ;
		}
		envp++;
	}
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_command_path(char *cmd, char **envp)
{
	char **paths;
	char *full_path;
	int i;
	size_t path_len;

	if (!cmd || !envp || !*envp)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = parse_path(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(path_len);
		if (!full_path)
		{
			free_paths(paths);
			return (NULL);
		}
		ft_strlcpy(full_path, paths[i], path_len);
		ft_strlcat(full_path, "/", path_len);
		ft_strlcat(full_path, cmd, path_len);
		if (access(full_path, X_OK) == 0)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}