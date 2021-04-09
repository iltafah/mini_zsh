#include "create_abstract_syntax_tree.h"

void change_nodes_state(t_state *state, t_type token)
{
    initialize_node_vars(state);
    if (token == e_simple_word)
    {
        state->pipe_seq_node = EXIST;
        state->simple_command_node = EXIST;
        state->word_node = EXIST;
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
    // t_ast_ptrs ast_ptrs;
    // t_state state;

    initialize_node_vars(&vars.state);
    initialize_ast_pointers(&vars.ast_ptrs);
    *ast = create_single_node(e_cmdline_node);
    vars.ast_ptrs.cmd_line_node = ast;
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
        //else if (curr_token->type == e_redir)
        //    store_redirection_data(&ast_ptrs, &curr_token);
        curr_token = curr_token->next;
    }
}