#include "../readline.h"

void	move_cursor_start_of_next_line(t_rdline *rdl_vars)
{
	move_cursor_to_colum(rdl_vars, 0);
	move_cursor_down_vertically(rdl_vars);
}
