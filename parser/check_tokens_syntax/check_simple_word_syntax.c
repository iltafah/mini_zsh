#include "check_tokens_syntax.h"
#include "../usefull_functions/usefull_functions.h"

// void    open_and_close_double_quotes(t_vars *vars)
// {
//     if (vars->backslash == NONE 
//     && vars->single_quotes == CLOSED
//     && vars->double_quotes == CLOSED)
//     {
//         vars->double_quotes = OPEND;
//     }
//     else if (vars->backslash == NONE
//     && vars->double_quotes == OPEND)
//     {
//         vars->double_quotes = CLOSED;
//     }
// }

// void    open_and_close_single_quotes(t_vars *vars)
// {
//     if (vars->backslash == NONE
//     && vars->double_quotes == CLOSED
//     && vars->single_quotes == CLOSED)
//     {
//         vars->single_quotes = OPEND;
//     }
//     else if (vars->single_quotes == OPEND)
//     {
//         vars->single_quotes = CLOSED;
//     }
// }

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
	t_quotes	quotes;

    i = 0;
	initialize_quotes_vars(&quotes);
    while (token[i] != '\0')
    {
        open_and_close_quotes(token[i], &quotes);
        does_backslash_exist(token[i], &quotes);
        i++;
    }
    if (quotes.double_quotes == OPEND || quotes.single_quotes == OPEND
    || quotes.backslash == EXIST)
    {
        vars->error = EXIST;
        printf("%s> Error: multiline commands not allowed\n", RED);
    }
}