/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:02:03 by nsahakya          #+#    #+#             */
/*   Updated: 2025/10/23 19:42:37 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static bool	match_pattern(const char *filename, const char *pattern)
{
	if (*pattern == '\0')
		return (*filename == '\0');
	if (*pattern == (char)WILDCARD_SYMBOL)
	{
		while (*pattern == (char)WILDCARD_SYMBOL)
			pattern++;
		if (*pattern == '\0')
			return (true);
		while (*filename)
		{
			if (match_pattern(filename, pattern))
				return (true);
			filename++;
		}
		return (false);
	}
	if (*pattern == *filename)
		return (match_pattern(filename + 1, pattern + 1));
	return (false);
}

static int	add_matching_files(t_strvector *args, const char *pattern)
{
	DIR				*directory;
	struct dirent	*file;
	int				found_files_count;

	found_files_count = 0;
	directory = opendir(".");
	if (!directory)
		return (-1);
	while (true)
	{
		file = readdir(directory);
		if (!file)
			break ;
		if ((file->d_name[0] == '.' && pattern[0] != '.')
			|| !ft_strcmp(file->d_name, ".") || !ft_strcmp(file->d_name, ".."))
			continue ;
		if (match_pattern(file->d_name, pattern))
		{
			if (!ft_sv_push_back_dup(args, file->d_name))
				return (closedir(directory), -1);
			found_files_count++;
		}
	}
	return (closedir(directory), found_files_count);
}

void	recover_pattern(char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == (char)WILDCARD_SYMBOL)
			pattern[i] = '*';
		i++;
	}
}

bool	expand_wildcard(t_strvector *args, char *pattern)
{
	int	found_files_count;

	found_files_count = 0;
	if (!ft_strchr(pattern, (char)WILDCARD_SYMBOL))
		return (recover_pattern(pattern), ft_sv_push_back_dup(args, pattern));
	found_files_count = add_matching_files(args, pattern);
	if (found_files_count < 0)
		return (false);
	if (found_files_count == 0)
		return (recover_pattern(pattern), ft_sv_push_back_dup(args, pattern));
	return (true);
}
