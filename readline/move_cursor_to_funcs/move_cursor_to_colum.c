#include "../readline.h"

void	move_cursor_to_colum(t_rdline *rdl_vars, int col)
{
	tputs(tgoto(rdl_vars->capability.mv_cursor_to_colm, 0, col), 1, put_char);
	rdl_vars->curs_colm_pos = col;
}
