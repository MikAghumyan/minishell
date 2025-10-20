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