#include "create_abstract_syntax_tree.h"

t_redirection	*create_single_redirection_node(char *type, char *file)
{
	t_redirection *new_redirection_node;

	new_redirection_node = malloc(sizeof(t_redirection));
	new_redirection_node->type = type;
	new_redirection_node->file = file;
	new_redirection_node->next = NULL;
	return (new_redirection_node);
}

void	store_redir_in_suitable_node(t_ast_vars *vars, t_tokens **curr_token)
{
	t_redirection **curr_redir_node;
	char *type;
	char *file;

	if (vars->ast_ptrs.curr_data == NULL)
		get_suitable_nodes(vars->state, &vars->ast_ptrs);
	curr_redir_node = &((*vars->ast_ptrs.curr_data)->node.data.redirections);
	while (*curr_redir_node != NULL)
		curr_redir_node = &((*curr_redir_node)->next);
	type = (*curr_token)->data;
	(*curr_token) = (*curr_token)->next;
	file = (*curr_token)->data;
	*curr_redir_node = create_single_redirection_node(type, file);
}
