#include "check_tokens_syntax.h"

void    check_pipe_token_order(t_vars *vars)
{
    if (vars->command == NONE)// || vars->redirection == EXIST)
    {
        printf("%sbash: syntax error near unexpected token `|'\n", RED);
        vars->error = EXIST;
    }
    remember_last_token(vars, e_pipe);
}

void    check_semicolon_token_order(t_vars *vars)
{
    if (vars->command == NONE)// || vars->redirection == EXIST)
    {
        printf("%sbash: syntax error near unexpected token `;'\n", RED);
        vars->error = EXIST;
    }
    remember_last_token(vars, e_semicolon);
}

void    check_redirection_token_order(t_vars *vars)
{
    if (vars->redirection == EXIST)
    {
        printf("%sbash: syntax error near unexpected token `>'\n", RED);
        vars->error = EXIST;
    }
    remember_last_token(vars, e_redir);
}

void    check_newline_token_order(t_vars *vars)
{
    if (vars->redirection == EXIST)
    {
        printf("%sbash: syntax error near unexpected token `newline'\n", RED);
        vars->error = EXIST;
    }
    else if (vars->pipe == EXIST)
    {
        printf("%s> Error: multiline commands not allowed\n", RED);
        vars->error = EXIST;
    }
}

void    check_word_token_order(t_vars *vars, char *token)
{
    check_simple_word_syntax(token);
    remember_last_token(vars, e_simple_word);
}