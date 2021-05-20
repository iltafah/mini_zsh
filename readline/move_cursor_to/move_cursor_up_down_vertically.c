#include "../readline.h"

void	move_cursor_up_vertically(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_up_vertically, 1, put_char);
	rdl_vars->curs_row_pos--;
}

void	move_cursor_down_vertically(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_down_vertically, 1, put_char);
	rdl_vars->curs_row_pos++;
}
