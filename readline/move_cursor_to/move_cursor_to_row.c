#include "../readline.h"

void	move_cursor_to_row(t_rdline *rdl_vars, int row)
{
	if (row > rdl_vars->curs_row_pos && row < (rdl_vars->printed_lines - 1))
		move_cursor_down_vertically(rdl_vars);
	else if (row > 0)
		move_cursor_up_vertically(rdl_vars);
}