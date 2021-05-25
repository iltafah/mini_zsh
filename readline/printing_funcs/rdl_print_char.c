#include "../readline.h"

void	rdl_print_char(t_rdline *rdl_vars, char c, char *color)
{
	put_colorful_char(c, color);
	rdl_vars->curs_colm_pos++;
	if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
	{
		put_char(' ');
		move_cursor_left(rdl_vars);
		rdl_vars->curs_row_pos++;
		rdl_vars->curs_colm_pos = 0;
		clear_curr_line_after_cursor(rdl_vars);
	}
}
