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

void     check_simple_word_syntax(char *token, t_vars *vars)
{
    int     i;

    i = 0;
    vars->backslash = NONE;
    vars->double_quotes = NONE;
    vars->single_quotes = NONE;
    while (token[i] != '\0')
    {
        if (token[i] == DOUBLE_QUOTES)
            open_and_close_double_quotes(vars);
        else if (token[i] == SINGLE_QUOTES)
            open_and_close_single_quotes(vars);
        if (token[i] == BACKSLASH && vars->backslash == NONE)
            vars->backslash = EXIST;
        else
            vars->backslash = NONE;
        i++;
    }
    if (vars->double_quotes == OPEND || vars->single_quotes == OPEND
    || vars->backslash == EXIST)
    {
        vars->error = EXIST;
        printf("%s> Error: multiline commands not allowed\n", RED);
    }
}