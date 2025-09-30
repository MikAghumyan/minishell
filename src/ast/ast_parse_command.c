#include "../../includes/ast.h"

static void	add_redirect_to_end(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect	*current;

	if (!head || !new_redirect)
		return ;
	if (*head == NULL)
	{
		*head = new_redirect;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_redirect;
}

char	**collect_ast_arguments(t_token **tokens, int *arg_count)
{
	char	**args;
	char	**temp;
	int		count;

	if (!tokens || !*tokens || !arg_count)
		return (NULL);
	args = NULL;
	count = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		temp = ft_realloc(args,
				sizeof(char *) * (count), sizeof(char *) * (count + 2));
		if (!temp)
			return (free_collected_args(args, &count));
		args = temp;
		args[count] = ft_strdup((*tokens)->value);
		if (!args[count])
			return (free_collected_args(args, &count));
		count++;
		*tokens = (*tokens)->next;
	}
	if (args)
		args[count] = NULL;
	*arg_count = count;
	return (args);
}

t_ast_node	*ast_parse_simple_command(t_token **tokens)
{
	t_ast_node	*cmd_node;
	char		**args;
	int			arg_count;

	if (!tokens || !*tokens)
		return (NULL);
	args = collect_ast_arguments(tokens, &arg_count);
	if (arg_count > 0)
	{
		cmd_node = create_ast_node(NODE_COMMAND);
		if (!cmd_node)
			return (free_simple_command_args(args));
		cmd_node->args = args;
		return (cmd_node);
	}
	if (args)
		free(args);
	return (NULL);
}

t_ast_node	*ast_parse_redirections(t_token **tokens, t_ast_node *cmd_node)
{
	t_redirect		*redirect;
	t_node_type		redirect_type;
	char			**new_args;
	int				current_arg_count;
	int				additional_args;
	char			**additional_args_array;
	int				i;

	if (!tokens || !*tokens || !cmd_node)
		return (cmd_node);
	current_arg_count = 0;
	if (cmd_node->args)
	{
		while (cmd_node->args[current_arg_count])
			current_arg_count++;
	}
	while (*tokens && (is_redirect_ast_token(*tokens) || (*tokens)->type == TOKEN_WORD))
	{
		if (is_redirect_ast_token(*tokens))
		{
			if ((*tokens)->type == TOKEN_REDIRECT_IN)
				redirect_type = NODE_REDIRECT_IN;
			else if ((*tokens)->type == TOKEN_REDIRECT_OUT)
				redirect_type = NODE_REDIRECT_OUT;
			else if ((*tokens)->type == TOKEN_APPEND)
				redirect_type = NODE_APPEND;
			else if ((*tokens)->type == TOKEN_HEREDOC)
				redirect_type = NODE_HEREDOC;
			*tokens = (*tokens)->next;
			if (*tokens && (*tokens)->type == TOKEN_WORD)
			{
				redirect = malloc(sizeof(t_redirect));
				if (!redirect)
				{
					ft_putstr_fd("minishell: memory allocation error\n", 2);
					return (cmd_node);
				}
				redirect->type = redirect_type;
				redirect->filename = ft_strdup((*tokens)->value);
				if (!redirect->filename)
				{
					free(redirect);
					ft_putstr_fd("minishell: memory allocation error\n", 2);
					return (cmd_node);
				}
				redirect->next = NULL;
				add_redirect_to_end(&cmd_node->redirect_files, redirect);
				*tokens = (*tokens)->next;
			}
			else
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				break ;
			}
		}
		else if ((*tokens)->type == TOKEN_WORD)
		{
			additional_args_array = collect_ast_arguments(tokens, &additional_args);
			if (additional_args > 0)
			{
				new_args = malloc(sizeof(char *) * (current_arg_count + additional_args + 1));
				if (!new_args)
				{
					i = 0;
					while (i < additional_args)
					{
						free(additional_args_array[i]);
						i++;
					}
					free(additional_args_array);
					return (cmd_node);
				}
				i = 0;
				while (i < current_arg_count)
				{
					new_args[i] = cmd_node->args[i];
					i++;
				}
				i = 0;
				while (i < additional_args)
				{
					new_args[current_arg_count + i] = additional_args_array[i];
					i++;
				}
				new_args[current_arg_count + additional_args] = NULL;
				free(cmd_node->args);
				free(additional_args_array);
				cmd_node->args = new_args;
				current_arg_count += additional_args;
			}
		}
	}
	return (cmd_node);
}
