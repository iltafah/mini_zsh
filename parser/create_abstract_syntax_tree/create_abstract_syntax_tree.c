#include "create_abstract_syntax_tree.h"

void change_nodes_state(t_state *state, t_type token)
{
    initialize_node_states(state);
    if (token == e_simple_word || token == e_redir)
    {
        state->pipe_seq_node = EXIST;
        state->simple_command_node = EXIST;
        state->data_node = EXIST;
    }
    else if (token == e_pipe)
    {
        state->pipe_seq_node = EXIST;
        state->simple_command_node = EXIST;
    }
    else if (token == e_semicolon)
        state->pipe_seq_node = EXIST;
}

void create_abstract_syntax_tree(t_ast **ast, t_tokens *tokens)
{
	t_ast_vars	vars;
    t_tokens	*curr_token;

	initialize_ast_vars(&vars);
    *ast = create_single_node(e_cmdline_node);
    vars.ast_ptrs.cmd_line = ast;
    curr_token = tokens;
    while (curr_token)
    {
        if (curr_token->type == e_simple_word)
        {
            store_word_in_suitable_node(&vars, curr_token->data);
            change_nodes_state(&vars.state, e_simple_word);
        }
        else if (curr_token->type == e_pipe)
            change_nodes_state(&vars.state, e_pipe);
        else if (curr_token->type == e_semicolon)
            change_nodes_state(&vars.state, e_semicolon);
        else if (curr_token->type == e_redir)
		{
            store_redir_in_suitable_node(&vars, &curr_token);
			change_nodes_state(&vars.state, e_redir);
		}
        curr_token = curr_token->next;
    }
}