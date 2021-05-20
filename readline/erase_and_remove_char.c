#include "readline.h"

void	erase_and_remove_curr_char(t_rdline *rdl_vars)
{
	t_vchar_vec	*history_vec;
	t_char_vec	*hstry_line;
	int			*curs_colm_pos;
	int			*l_i;
	int			*c_i;

	c_i = &rdl_vars->c_i;
	l_i = &rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	hstry_line = history_vec->elements;
	curs_colm_pos = &rdl_vars->curs_colm_pos;
	if (*c_i > 0)
	{
		(*c_i)--;
		hstry_line[*l_i].delete_element_at_index(&hstry_line[*l_i], *c_i);
		if (*curs_colm_pos == 0)
			move_cursor_end_of_prec_line(rdl_vars);
		else
			move_cursor_left(rdl_vars);
		print_after_cursor(rdl_vars, hstry_line[*l_i].elements + *c_i, restore);
		update_cursor_data(rdl_vars);
	}
}
