#include "readline.h"

void	restore_cursor_pos(t_rdline *rdl_vars)
{
	while (rdl_vars->curs_row_pos > rdl_vars->curs_row_old_pos)
		move_cursor_up_vertically(rdl_vars);
	move_cursor_to_colum(rdl_vars, rdl_vars->curs_colm_old_pos);
}

void	save_curr_cursor_pos(t_rdline *rdl_vars)
{
	rdl_vars->curs_row_old_pos = rdl_vars->curs_row_pos;
	rdl_vars->curs_colm_old_pos = rdl_vars->curs_colm_pos;
}
