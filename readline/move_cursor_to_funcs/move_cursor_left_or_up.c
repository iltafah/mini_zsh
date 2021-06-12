#include "../readline.h"

void	move_cursor_left_or_up(t_rdline *rdl_vars)
{
	if (rdl_vars->curs_colm_pos > 0)
		move_cursor_left(rdl_vars);
	else
		move_cursor_end_of_prec_line(rdl_vars);
}
