#include "../../includes/ast.h"

t_ast_node	*build_ast(t_shell *shell)
{
	t_parser	parser;
	t_ast_node	*result;

	if (!shell->tokens)
		return (NULL);
	parser.tokens = shell->tokens;
	parser.subshell_depth = 0;
	parser.syserror = false;
	parser.shell = shell;
	result = ast_parse_logical(&parser);
	if (!result)
	{
		if (parser.syserror)
			exit_shell_with_error(shell, "minishell: system error");
		if (parser.tokens)
			ft_fprintf(2,
				"minishell: syntax error near unexpected token `%s'\n",
				parser.tokens->value);
		else
			ft_fprintf(2, "minishell: syntax error: unexpected end of line\n");
		shell->exit_status = 2;
	}
	// printf("\n=== AST TREE ===\n");
	// print_ast(result, 0);
	// printf("================\n\n");
	return (result);
}

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirect_files = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			node->args[i] = NULL;
			i++;
		}
		free(node->args);
	}
	if (node->redirect_files)
		ft_lstclear(&node->redirect_files, free_redirect);
	free_ast(node->right);
	free_ast(node->left);
	free(node);
}

// void	print_ast(t_ast_node *node, int depth)
// // no need here to fix norme errors, it's just a debug function
// {
// 	int i;
// 	t_redirect *redirect;

// 	if (!node)
// 		return ;

// 	for (i = 0; i < depth; i++)
// 		printf("  ");

// 	switch (node->type)
// 	{
// 	case NODE_COMMAND:
// 		printf("COMMAND: ");
// 		if (node->args)
// 		{
// 			i = 0;
// 			while (node->args[i])
// 			{
// 				printf("%s ", node->args[i]);
// 				i++;
// 			}
// 		}
// 		if (node->redirect_files)
// 		{
// 			t_list *current_list;
// 			printf("(redirects: ");
// 			current_list = node->redirect_files;
// 			while (current_list)
// 			{
// 				redirect = (t_redirect *)current_list->content;
// 				printf("[%d:%s] ", redirect->type, redirect->filename);
// 				current_list = current_list->next;
// 			}
// 			printf(")");
// 		}
// 		break ;
// 	case NODE_PIPE:
// 		printf("PIPE");
// 		break ;
// 	case NODE_AND:
// 		printf("AND");
// 		break ;
// 	case NODE_OR:
// 		printf("OR");
// 		break ;
// 	case NODE_SUBSHELL:
// 		printf("SUBSHELL");
// 		if (node->redirect_files)
// 		{
// 			t_list *current_list;
// 			printf(" (redirects: ");
// 			current_list = node->redirect_files;
// 			while (current_list)
// 			{
// 				redirect = (t_redirect *)current_list->content;
// 				printf("[%d:%s] ", redirect->type, redirect->filename);
// 				current_list = current_list->next;
// 			}
// 			printf(")");
// 		}
// 		break ;
// 	default:
// 		printf("UNKNOWN");
// 	}
// 	printf("\n");

// 	if (node->left)
// 		print_ast(node->left, depth + 1);
// 	if (node->right)
// 		print_ast(node->right, depth + 1);
// }
