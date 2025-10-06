#include "../../includes/ast.h"

static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

static void	print_redirects(t_list *redirect_list)
{
	t_redirect	*redirect;
	t_list		*current_list;

	if (!redirect_list)
		return ;
	printf("(redirects: ");
	current_list = redirect_list;
	while (current_list)
	{
		redirect = (t_redirect *)current_list->content;
		printf("[%d:%s] ", redirect->type, redirect->filename);
		current_list = current_list->next;
	}
	printf(")");
}

static void	print_command(t_ast_node *node)
{
	int	i;

	i = 0;
	printf("COMMAND: ");
	while (node->args && node->args[i])
	{
		printf("%s ", node->args[i]);
		i++;
	}
	if (node->redirect_files)
		print_redirects(node->redirect_files);
}

void	print_ast(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	if (node->type == NODE_COMMAND)
		print_command(node);
	else if (node->type == NODE_PIPE)
		printf("PIPE");
	else if (node->type == NODE_AND)
		printf("AND");
	else if (node->type == NODE_OR)
		printf("OR");
	else if (node->type == NODE_SUBSHELL)
		printf("SUBSHELL");
	else
		printf("UNKNOWN");
	printf("\n");
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
