#include "../readline.h"

void	move_to_beginning_of_line(t_rdline *rdl_vars)
{
	if (rdl_vars->c_i > 0)
	{
		while (rdl_vars->curs_row_pos > 0)
			move_cursor_up_vertically(rdl_vars);
		move_cursor_to_colum(rdl_vars, rdl_vars->prompt_len);
		rdl_vars->c_i = 0;
	}
}
