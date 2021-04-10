#include "create_abstract_syntax_tree.h"

void	get_curr_pipe_seq_node(t_state state, t_ast_ptrs *ast)
{
	if (state.pipe_seq_node == NONE)
		ast->curr_pipe_seq = create_pipe_seq_node(ast->cmd_line, BOTTOM);
	else if (state.simple_command_node == NONE)
		ast->curr_pipe_seq = create_pipe_seq_node(ast->curr_pipe_seq, NEXT);
}

void	get_curr_simple_cmd_node(t_state state, t_ast_ptrs *ast)
{
	if (state.simple_command_node == NONE)
		ast->curr_smpl_cmd = create_smpl_cmd_node(ast->curr_pipe_seq, BOTTOM);
	else if (state.data_node == NONE)
		ast->curr_smpl_cmd = create_smpl_cmd_node(ast->curr_smpl_cmd, NEXT);
}

void	get_curr_data_node(t_state state, t_ast_ptrs *ast)
{
	if (state.data_node == NONE)
		ast->curr_data = create_data_node(ast->curr_smpl_cmd, BOTTOM);
	else if (state.data_node == EXIST)
		ast->curr_data = ast->curr_data;
			//create_word_node(ast->curr_word_node, NEXT);
}

void	store_word_in_suitable_node(t_ast_vars *vars, char *word)
{
	get_curr_pipe_seq_node(vars->state, &vars->ast_ptrs);
	get_curr_simple_cmd_node(vars->state, &vars->ast_ptrs);
	get_curr_data_node(vars->state, &vars->ast_ptrs);
	vars->dynamic_table.ptr = &((*vars->ast_ptrs.curr_data)->node.data.args);
	dynamic_table_join(&vars->dynamic_table, word);
	(*vars->ast_ptrs.curr_data)->node.data.args = *vars->dynamic_table.ptr;
}
