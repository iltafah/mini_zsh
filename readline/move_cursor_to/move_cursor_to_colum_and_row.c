#include "../readline.h"

void	move_cursor_to_colum_and_row(t_rdline *rdl_vars, int col, int row)
{
	move_cursor_to_colum(rdl_vars, col);
	move_cursor_to_row(rdl_vars, row);
}