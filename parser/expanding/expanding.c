#include "./expanding.h"

void	expand_args_vec(t_str_vec *args_vec, t_env_table env_table)
{
	int			i;

	i = 0;
	while (args_vec->elements[i])
	{
		give_quotes_special_meaning(args_vec->elements[i]);
		expand_dollar_vars(&args_vec->elements[i], env_table);
		split_element_to_args(args_vec, &i);
	}
}

void	expand_redirection_list(t_redirection *rdir_list, t_env_table env_table)
{
	t_redirection *curr_redir_node;

	curr_redir_node = rdir_list;
	while (curr_redir_node != NULL)
	{
		give_quotes_special_meaning(curr_redir_node->file);
		expand_dollar_vars(&curr_redir_node->file, env_table);
		curr_redir_node = curr_redir_node->next;
	}
}

void	expand_curr_cmd(t_ast *curr_simple_cmd, t_env_table env_table)
{
	t_ast	*data;

	data = curr_simple_cmd->node.dir.bottom;
	expand_args_vec(&data->node.data.args_vec, env_table);
	expand_redirection_list(data->node.data.redirections, env_table);
}



//[cat]  ["hello   world"] [$vscode]  [$vscode]