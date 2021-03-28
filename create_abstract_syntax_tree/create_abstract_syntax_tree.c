#include "create_abstract_syntax_tree.h"

void    create_abstract_syntax_tree(t_node **cmd_line_node, t_tokens *tokens)
{
    t_tokens    *curr_token;
    t_node      **curr_pipe_seq_node;
    t_node      **curr_simple_cmd_node;
    t_node      **curr_word_node;

    int         dir;
    int         word = NONE;
    int         simple_cmd = NONE;
    int         semicolon = NONE;
    int         pipe = NONE;

    *cmd_line_node = create_single_node();
    curr_pipe_seq_node = get_node(cmd_line_node, BOTTOM);
    fill_pipeline(curr_pipe_seq_node);
    // curr_simple_cmd_node = get_node(curr_pipe_seq_node, BOTTOM);
    // curr_word_node = get_node(curr_simple_cmd_node, BOTTOM);

    curr_token = tokens;
    while (curr_token)
    {
        if (curr_token->type == e_simple_word)
        {
            if (semicolon == EXIST && word == NONE)
            {
                curr_pipe_seq_node = get_node(curr_pipe_seq_node, NEXT);
                fill_pipeline(curr_pipe_seq_node);
            }
            if (word == NONE && simple_cmd == NONE)
            {
                curr_simple_cmd_node = get_node(curr_pipe_seq_node, BOTTOM);
                fill_cmd_node(curr_simple_cmd_node);
            }
           
            if (word == EXIST)
                curr_word_node = get_node(curr_word_node, NEXT);
            else
                curr_word_node = get_node(curr_simple_cmd_node, BOTTOM);
            fill_word_node(curr_word_node, curr_token->data);
            
            word = EXIST;
            simple_cmd = EXIST;
            semicolon = NONE;
            pipe = NONE;
        }
        else if (curr_token->type == e_pipe)
        {
            curr_simple_cmd_node = get_node(curr_simple_cmd_node, NEXT);
            fill_cmd_node(curr_simple_cmd_node);
            simple_cmd = EXIST;
            pipe = EXIST;
            word = NONE;
            semicolon = NONE;
        }
        else if (curr_token->type == e_semicolon)
        {
            semicolon = EXIST;
            word = NONE;
            pipe = NONE;
            simple_cmd = NONE;
        }
        curr_token = curr_token->next;
    }
}