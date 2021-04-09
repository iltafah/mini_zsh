#include "create_abstract_syntax_tree.h"

void	get_curr_pipe_seq_node(t_state state, t_ast_ptrs *ast)
{
	if (state.pipe_seq_node == NONE)
		ast->curr_pipe_seq_node =
			create_pipe_seq_node(ast->cmd_line_node, BOTTOM);
	else if (state.simple_command_node == NONE)
		ast->curr_pipe_seq_node =
			create_pipe_seq_node(ast->curr_pipe_seq_node, NEXT);
}

void	get_curr_simple_cmd_node(t_state state, t_ast_ptrs *ast)
{
	if (state.simple_command_node == NONE)
		ast->curr_simple_cmd_node =
			create_simple_cmd_node(ast->curr_pipe_seq_node, BOTTOM);
	else if (state.word_node == NONE)
		ast->curr_simple_cmd_node =
			create_simple_cmd_node(ast->curr_simple_cmd_node, NEXT);
}

void	get_curr_word_node(t_state state, t_ast_ptrs *ast)
{
	if (state.word_node == NONE)
		ast->curr_word_node =
			create_word_node(ast->curr_simple_cmd_node, BOTTOM);
	else if (state.word_node == EXIST)
		ast->curr_word_node = ast->curr_word_node;
			//create_word_node(ast->curr_word_node, NEXT);
}

void	dynamic_table_join(t_dynamic_table *dynamic_table, char *word)
{
	int		i;
	char	**new_table;

	i = 0;
	if (*dynamic_table->table_ptr == NULL)
	{
		dynamic_table->size = 2;
		dynamic_table->used_size = 0;
	}
	if (dynamic_table->used_size == dynamic_table->size)
		dynamic_table->size *= 2;

	new_table = malloc(sizeof(char*) * (dynamic_table->size + 1));
	while (i < dynamic_table->used_size)
	{
		new_table[i] = ft_strdup((*dynamic_table->table_ptr)[i]);
		i++;
	}
	new_table[i++] = ft_strdup(word);
	new_table[i] = NULL;
	if (*dynamic_table->table_ptr != NULL)
		free(*dynamic_table->table_ptr);
	dynamic_table->table_ptr = &new_table;
	dynamic_table->used_size += 1;
	// (*dynamic_table->table_ptr)[0] = ft_strdup("told ya\n");
	// (*dynamic_table->table_ptr)[1] = 0;
}

void	store_word_in_suitable_node(t_ast_vars *vars, char *word)
{
	get_curr_pipe_seq_node(vars->state, &vars->ast_ptrs);
	get_curr_simple_cmd_node(vars->state, &vars->ast_ptrs);
	get_curr_word_node(vars->state, &vars->ast_ptrs);

	char	***table_ptr;
	table_ptr = &(vars->ast_ptrs.curr_word_node[0]->node.data.args);

	vars->dynamic_table.table_ptr = table_ptr;
	dynamic_table_join(&vars->dynamic_table, word);
	vars->ast_ptrs.curr_word_node[0]->node.data.args = *vars->dynamic_table.table_ptr;

	//table_ptr = vars->dynamic_table.table_ptr;
	//printf("[%s]\n", vars->ast_ptrs.curr_word_node[0]->node.data.args[0]);
	//ast->curr_word_node[0]->u_infos.word = ft_strdup(word);
}
