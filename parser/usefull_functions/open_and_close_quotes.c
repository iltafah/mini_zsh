#include "./usefull_functions.h"

void    open_and_close_double_quotes(t_quotes *quotes)
{
    if (quotes->backslash == NONE 
    && quotes->single_quotes == CLOSED
    && quotes->double_quotes == CLOSED)
    {
        quotes->double_quotes = OPEND;
    }
    else if (quotes->backslash == NONE
    && quotes->double_quotes == OPEND)
    {
        quotes->double_quotes = CLOSED;
    }
}

void    open_and_close_single_quotes(t_quotes *quotes)
{
    if (quotes->backslash == NONE
    && quotes->double_quotes == CLOSED
    && quotes->single_quotes == CLOSED)
    {
        quotes->single_quotes = OPEND;
    }
    else if (quotes->single_quotes == OPEND)
    {
        quotes->single_quotes = CLOSED;
    }
}

void	initialize_quotes_vars(t_quotes *quotes)
{
	quotes->backslash = NONE;
	quotes->double_quotes = NONE;
	quotes->single_quotes = NONE;
}