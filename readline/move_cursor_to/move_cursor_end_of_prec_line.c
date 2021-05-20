#include "../readline.h"

void	move_cursor_end_of_prec_line(t_rdline *rdl_vars)
{
	move_cursor_up_vertically(rdl_vars);
	move_cursor_to_colum(rdl_vars, rdl_vars->width_of_screen - 1);
}
