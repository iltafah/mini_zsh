#include "../readline.h"

void	rdl_print_char(t_rdline *rdl_vars, char c, char *color)
{
	write(1, color, ft_strlen(color));
	put_char(c);
	rdl_vars->curs_colm_pos++;
	if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
	{
		put_char(' ');
		move_cursor_left(rdl_vars);
		rdl_vars->curs_row_pos++;
		rdl_vars->curs_colm_pos = 0;
	}
}
