#include "check_tokens_syntax.h"

void    remember_last_token(t_vars *vars, t_type token)
{
    vars->command = NONE;
    vars->pipe = NONE;
    vars->redirection = NONE;
    if (token == e_simple_word)
        vars->command = EXIST;
    else if (token == e_pipe)
        vars->pipe = EXIST;
    else if (token == e_redir)
        vars->redirection = EXIST;
}

void    initialize_tokens_vars(t_vars *vars)
{
    vars->command = NONE;
    vars->redirection = NONE;
    vars->pipe = NONE;
    vars->error = NONE;
}

int     check_tokens_syntax(t_tokens *tokens_list)
{
    t_tokens    *curr_token_node;
    t_vars      vars;

    curr_token_node = tokens_list;
    initialize_tokens_vars(&vars);
    while (curr_token_node && vars.error == NONE)
    {
        if (curr_token_node->type == e_simple_word)
            check_word_token_order(&vars, curr_token_node->data);
        else if (curr_token_node->type == e_pipe)
            check_pipe_token_order(&vars);
        else if (curr_token_node->type == e_semicolon)
            check_semicolon_token_order(&vars);
        else if (curr_token_node->type == e_redir)
            check_redirection_token_order(&vars);
        else if (curr_token_node->type == newline)
            check_newline_token_order(&vars);
        curr_token_node = curr_token_node->next;
    }
    if (vars.error == EXIST)
        return (ERROR);
    return (VALID);
}

        // {
            //if (check_simple_word_syntax(curr_token_node->data) == ERROR)
            //{
                // printf("%s> Error: multiline commands not allowed\n", RED);
                //return (ERROR);
            // //}
            // check_simple_word_syntax(curr_token_node->data);
            // remember_last_token(&vars, e_simple_word);
            // vars.command = EXIST;
            // vars.redirection = NONE;
            // vars.pipe = NONE;
        // }
        // {
            // if (vars.command == NONE || vars.redirection == EXIST)
            // {
            //     printf("%sbash: syntax error near unexpected token `|'\n", RED);
            //     vars.error = EXIST;
            // }
            // remember_last_token(&vars, e_simple_cmd_node);
            // else if (curr_token_node->next == NULL)
            // {
            //     printf("%s> Error: multiline commands not allowed\n", RED);
            //     return (ERROR);
            // }
            // vars.pipe = EXIST;
            // vars.command = NONE;
            // vars.redirection = NONE;
        // }
        // {
            // if (vars.command == NONE || vars.redirection == EXIST)
            // {
            //     printf("%sbash: syntax error near unexpected token `;'\n", RED);
            //     vars.error = EXIST;
            // }
            // remember_last_token(&vars, e_simple_cmd_node);
            // vars.command = NONE;
            // vars.redirection = NONE;
            // vars.pipe = NONE;
        // }
        //{
            // vars.redirection = EXIST;
            // vars.pipe = NONE;
            // vars.command = NONE;
        //}

    // if (vars.redirection == EXIST)
    // {
    //     printf("%sbash: syntax error near unexpected token `newline'\n", RED);
    //     return (ERROR);
    // }
    // else if (vars.pipe == EXIST)
    // {
    //     printf("%s> Error: multiline commands not allowed\n", RED);
    //     return (ERROR);
    // }