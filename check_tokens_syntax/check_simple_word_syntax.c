# include "check_tokens_syntax.h"

void    open_and_close_double_quotes(t_vars *vars)
{
    if (vars->backslash == NONE 
    && vars->single_quotes == CLOSED
    && vars->double_quotes == CLOSED)
    {
        vars->double_quotes = OPEND;
    }
    else if (vars->backslash == NONE
    && vars->double_quotes == OPEND)
    {
        vars->double_quotes = CLOSED;
    }
}

void    open_and_close_single_quotes(t_vars *vars)
{
    if (vars->backslash == NONE
    && vars->double_quotes == CLOSED
    && vars->single_quotes == CLOSED)
    {
        vars->single_quotes = OPEND;
    }
    else if (vars->single_quotes == OPEND)
    {
        vars->single_quotes = CLOSED;
    }
}

// void    does_backslash_exist_or_not(t_vars *vars)
// {
//     if (vars->backslash == NONE)
//     {
//         vars->backslash = EXIST;
//     }
//     else
//     {
//         vars->backslash = NONE;
//     }
// }

int     check_simple_word_syntax(char *token)
{
    int     i;
    t_vars  vars;

    i = 0;
    vars.backslash = 0;
    vars.double_quotes = 0;
    vars.single_quotes = 0;
    while (token[i] != '\0')
    {
        if (token[i] == DOUBLE_QUOTES)
            open_and_close_double_quotes(&vars);
        else if (token[i] == SINGLE_QUOTES)
            open_and_close_single_quotes(&vars);
        if (token[i] == BACKSLASH && vars.backslash == NONE)
            vars.backslash = EXIST;
        else
            vars.backslash = NONE;
        i++;
    }
    if (vars.double_quotes == OPEND || vars.single_quotes == OPEND
    || vars.backslash == EXIST)
    {
        return (ERROR);
    }
    return (TRUE);
}