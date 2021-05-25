#include "../readline.h"

void	print_curr_char(t_rdline *rdl_vars, char c)
{
	t_char_vec		*history_line;
	t_vchar_vec		*history_vec;
	int	*l_i;
	int	*c_i;

	c_i = &rdl_vars->c_i;
	l_i = &rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	history_line[*l_i].add_new_element_at_index(&history_line[*l_i], c, *c_i);
	rdl_print_char(rdl_vars, history_line[*l_i].elements[*c_i], WHT);
	(*c_i)++;
	print_after_cursor(rdl_vars, history_line[*l_i].elements + *c_i, restore);
	print_suggestions(rdl_vars);
	update_cursor_data(rdl_vars);
}

	// put_char(history_line[*l_i].elements[*c_i]);
	// rdl_vars->curs_colm_pos++;
	// if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
	// {
	// 	put_char(' ');
	// 	move_cursor_left(rdl_vars);
	// 	rdl_vars->curs_row_pos++;
	// 	rdl_vars->curs_colm_pos = 0;
	// }