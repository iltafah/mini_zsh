#include "./freeing_time.h"

void	free_redirection_list(t_redirection **redirection_list)
{
	t_redirection *curr_redir_node;
	t_redirection *next_redir_node;
	
	curr_redir_node = *redirection_list;
	while (curr_redir_node)
	{
		next_redir_node = curr_redir_node->next;
		free(curr_redir_node);
		curr_redir_node = next_redir_node;
	}
	*redirection_list = NULL;
}

void	free_args_vec(t_vec *args_vec)
{
	free(args_vec->elements);
	args_vec->elements = NULL;
}

void	free_data_node_content(t_data *node_data)
{
	free_args_vec(&node_data->args_vec);
	free_redirection_list(&node_data->redirections);
}

void	free_abstract_syntax_tree(t_ast *ast)
{
    if (ast == NULL)
        return;
	if (ast->tag != e_data_node)
	{
    	free_abstract_syntax_tree(ast->node.dir.bottom);
    	free_abstract_syntax_tree(ast->node.dir.next);
	}
	else
		free_data_node_content(&ast->node.data);
	free(ast);
}