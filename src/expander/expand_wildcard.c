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