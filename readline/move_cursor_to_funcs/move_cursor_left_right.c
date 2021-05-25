#include "../readline.h"

void	move_cursor_right(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_right, 1, put_char);
	rdl_vars->curs_colm_pos++;
}

void	move_cursor_left(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_left, 1, put_char);
	rdl_vars->curs_colm_pos--;
}
