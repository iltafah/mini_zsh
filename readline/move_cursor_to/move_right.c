#include "../readline.h"

void	move_right(t_rdline *rdl_vars)
{
	t_char_vec	*history_line;
	t_vchar_vec	*history_vec;
	int			*curs_colm_pos;
	int			*l_i;
	int			*c_i;

	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	curs_colm_pos = &rdl_vars->curs_colm_pos;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	if (*c_i < history_line[*l_i].used_size)
	{
		(*c_i)++;
		if (*curs_colm_pos == rdl_vars->width_of_screen - 1)
			move_cursor_start_of_next_line(rdl_vars);
		else
			move_cursor_right(rdl_vars);
		update_cursor_data(rdl_vars);
	}
}
