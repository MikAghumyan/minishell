#include "../../includes/ast.h"

char	**free_collected_args(char **args, int *count)
{
	if (!args)
		return (NULL);
	while (*count > 0)
	{
		(*count)--;
		free(args[*count]);
	}
	free(args);
	return (NULL);
}

t_ast_node	*free_simple_command_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (NULL);
}
