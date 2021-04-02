#include "create_abstract_syntax_tree.h"

void initialize_node_vars(t_state *state)
{
    state->pipe_seq_node = NONE;
    state->word_node = NONE;
    state->simple_command_node = NONE;
}

void    initialize_ast_pointers(t_ast_ptrs *ast)
{
    ast->cmd_line_node = NULL;
    ast->curr_pipe_seq_node = NULL;
    ast->curr_simple_cmd_node = NULL;
    ast->curr_word_node = NULL;
}