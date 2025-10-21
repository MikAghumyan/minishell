/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahakya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:02:03 by nsahakya          #+#    #+#             */
/*   Updated: 2025/10/21 13:02:12 by nsahakya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static bool	has_wildcard(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

static bool	match_pattern(const char *filename, const char *pattern)
{
	if (*pattern == '\0')
		return (*filename == '\0');
	if (*pattern == '*')
	{
		while (*pattern == '*')
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
	file = readdir(directory);
	while (file)
	{
		if (file->d_name[0] != '.'
			&& match_pattern(file->d_name, pattern))
		{
			if (!ft_sv_push_back_dup(args, file->d_name))
			{
				closedir(directory);
				return (-1);
			}
			found_files_count++;
		}
		file = readdir(directory);
	}
	closedir(directory);
	return (found_files_count);
}

bool	expand_wildcard(t_strvector *args, const char *pattern)
{
	int	found_files_count;

	found_files_count = 0;
	if (!has_wildcard(pattern))
		return (ft_sv_push_back_dup(args, pattern));
	found_files_count = add_matching_files(args, pattern);
	if (found_files_count < 0)
		return (false);
	if (found_files_count == 0)
		return (ft_sv_push_back_dup(args, pattern));
	return (true);
}
