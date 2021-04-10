#include "create_abstract_syntax_tree.h"

void	initialize_node_states(t_state *state)
{
    state->word_node = NONE;
    state->pipe_seq_node = NONE;
    state->simple_command_node = NONE;
}

void    initialize_ast_pointers(t_ast_ptrs *ast_ptrs)
{
    ast_ptrs->cmd_line = NULL;
    ast_ptrs->curr_data = NULL;
    ast_ptrs->curr_pipe_seq = NULL;
    ast_ptrs->curr_simple_cmd = NULL;
}

void	initialize_dynamic_table_vars(t_dynamic_table *dynamic_table)
{
	dynamic_table->size = 0;
	dynamic_table->ptr = NULL;
	dynamic_table->used_size = 0;
}

void	initialize_ast_vars(t_ast_vars *vars)
{
	initialize_node_states(&vars->state);
	initialize_ast_pointers(&vars->ast_ptrs);
	initialize_dynamic_table_vars(&vars->dynamic_table);
}