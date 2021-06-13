/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_close_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:39:52 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:39:53 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		does_backslash_exist(char c, t_quotes *quotes)
{
	if ((c == BACKSLASH || c == SPECIAL_BACKSLASH) && quotes->backslash == NONE)
	{
		quotes->backslash = EXIST;
		return (EXIST);
	}
	else
		quotes->backslash = NONE;
	return (NONE);
}

int		does_pipe_exist(char c, t_quotes *quotes)
{
	if (c == ' ')
		return (quotes->pipe);
	if (c == PIPE && quotes->backslash == NONE && quotes->curr_state == CLOSED)
	{
		quotes->pipe = EXIST;
		return (EXIST);
	}
	else
		quotes->pipe = NONE;
	return (NONE);
}

int		does_semicolon_exist(char c, t_quotes *quotes)
{
	if (c == ' ')
		return (quotes->semicolon);
	if (c == SEMICOLON && quotes->backslash == NONE
		&& quotes->curr_state == CLOSED)
	{
		quotes->semicolon = EXIST;
		return (EXIST);
	}
	else
		quotes->semicolon = NONE;
	return (NONE);
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
	quotes->pipe = NONE;
	quotes->semicolon = NONE;
	quotes->backslash = NONE;
    quotes->old_state = NONE;
    quotes->curr_state = NONE;
	quotes->double_quotes = NONE;
	quotes->single_quotes = NONE;
}