/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_command_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahakya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:00:29 by nsahakya          #+#    #+#             */
/*   Updated: 2025/10/21 13:00:30 by nsahakya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static char	*free_paths(char **paths)
{
	int	i;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	return (NULL);
}

static char	**parse_path(char **envp)
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

static char	*search_in_paths(const char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	size_t	path_len;

	if (!cmd || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(path_len);
		if (!full_path)
			return (NULL);
		ft_strlcpy(full_path, paths[i], path_len);
		ft_strlcat(full_path, "/", path_len);
		ft_strlcat(full_path, cmd, path_len);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*result;

	if (!cmd || !envp || !*envp)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = parse_path(envp);
	if (!paths)
		return (NULL);
	result = search_in_paths(cmd, paths);
	free_paths(paths);
	return (result);
}
