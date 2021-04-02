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
		ast->curr_word_node =
			create_word_node(ast->curr_word_node, NEXT);
}

void	store_word_in_suitable_node(t_state state, t_ast_ptrs *ast, char *word)
{
	get_curr_pipe_seq_node(state, ast);
	get_curr_simple_cmd_node(state, ast);
	get_curr_word_node(state, ast);
	ast->curr_word_node[0]->u_infos.word = ft_strdup(word);
}
