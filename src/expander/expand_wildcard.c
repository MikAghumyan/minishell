#include "../../includes/expander.h"

static bool has_wildcard(const char *str)
{
    size_t  i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '*')
            return (true);
        i++;
    }
    return (false);
}

static bool match_pattern(const char *filename, const char *pattern)
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

static  bool add_matching_files(t_strvector *args, const char *pattern)
{
    DIR             *directory;
    struct dirent   *file;

    directory = opendir(".");
    if (!directory)
        return (false);
    file = readdir(directory);
    while (file)
    {
        if (file->d_name[0] != '.' && (file->d_name, pattern)) //if it's hidden file we dont need to add it 
        {
            if (!ft_sv_push_back_dup(args, file->d_name))
            {
                closedir(directory);
                return (false);
            }
        }
        file = readdir(directory);
    }
    closedir(directory);
    return (true);
}

bool    expand_wildcard(t_strvector *args, const char *pattern)
{
    if (!has_wildcard(pattern))
        return (ft_sv_push_back_dup(args, pattern));
    // TODO: add_matching_files(args, pattern)
    return (true);
}