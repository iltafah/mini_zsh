#include "readline.h"

void	show_old_history(t_rdline *rdl_vars)
{
	t_char_vec		*history_line;
	t_vchar_vec		*history_vec;
	int	*l_i;
	int	*c_i;

	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	history_vec = &rdl_vars->history_vec;
	history_line = rdl_vars->history_vec.elements;
	if (*l_i > 0)
	{	
		(*l_i)--;
		clear_printed_lines(rdl_vars, dont_restore);
		print_after_cursor(rdl_vars, history_line[*l_i].elements, dont_restore);
		print_with_syntax_highlighting(rdl_vars);
		*c_i = history_line[*l_i].last_index + 1;
		update_cursor_data(rdl_vars);
		rdl_vars->is_matched_history = false;
	}
}

void	show_new_history(t_rdline *rdl_vars)
{
	t_char_vec		*history_line;
	t_vchar_vec		*history_vec;
	int	*l_i;
	int	*c_i;

	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	if (*l_i < history_vec->last_index)
	{
		(*l_i)++;
		clear_printed_lines(rdl_vars, dont_restore);
		print_after_cursor(rdl_vars, history_line[*l_i].elements, dont_restore);
		print_with_syntax_highlighting(rdl_vars);
		if (history_line[*l_i].used_size > 0)
			*c_i = history_line[*l_i].last_index + 1;
		else
			*c_i = 0;
		update_cursor_data(rdl_vars);
		rdl_vars->is_matched_history = false;
	}
}
