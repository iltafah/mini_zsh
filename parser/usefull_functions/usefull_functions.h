#ifndef USEFULL_FUNCTIONS_H
# define USEFULL_FUNCTIONS_H

# include "../../minishell.h"
typedef struct          s_quotes
{
    int                 backslash;
    int                 double_quotes;
    int                 single_quotes;
    int                 old_state;
    int                 curr_state;
}                       t_quotes;

// #define OPEND 1
// #define CLOSED 0

// #define NONE 0
// #define EXIST 1

void	initialize_quotes_vars(t_quotes *quotes);
void    open_and_close_double_quotes(t_quotes *quotes);
void    open_and_close_single_quotes(t_quotes *quotes);
void    open_and_close_quotes(char c, t_quotes *quotes);
void	change_quotes_state(t_quotes *quotes);

#endif