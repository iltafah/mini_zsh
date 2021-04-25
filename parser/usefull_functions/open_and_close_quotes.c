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

void    open_and_close_quotes(char c, t_quotes *quotes)
{
    if (c == SINGLE_QUOTES)
		open_and_close_single_quotes(quotes);
	else if (c == DOUBLE_QUOTES)
		open_and_close_double_quotes(quotes);
}

void    does_backslash_exist(char c, t_quotes *quotes)
{
	if ((c == BACKSLASH || c == SPECIAL_BACKSLASH) && quotes->backslash == NONE)
		quotes->backslash = EXIST;
	else
		quotes->backslash = NONE;
}

void		change_quotes_state(t_quotes *quotes)
{
	quotes->old_state = quotes->curr_state;
	if (quotes->single_quotes == OPEND || quotes->double_quotes == OPEND)
		quotes->curr_state = OPEND;
	else
		quotes->curr_state = CLOSED;
}

void	initialize_quotes_vars(t_quotes *quotes)
{
	quotes->backslash = NONE;
	quotes->double_quotes = NONE;
	quotes->single_quotes = NONE;
    quotes->old_state = NONE;
    quotes->curr_state = NONE;
}