#include "../readline.h"

void	print_after_cursor(t_rdline *rdl_vars, char *str, int option)
{
	int		i;

	i = 0;
	if (option == restore)
		save_curr_cursor_pos(rdl_vars);
	clear_curr_line_after_cursor(rdl_vars);
	while (str[i])
	{
		rdl_print_char(rdl_vars, str[i], WHT);
		i++;
	}
	if (option == restore)
		restore_cursor_pos(rdl_vars);
}

		// put_char(str[i++]);
		// rdl_vars->curs_colm_pos++;
		// if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
		// {
		// 	put_char(' ');
		// 	move_cursor_left(rdl_vars);
		// 	rdl_vars->curs_colm_pos = 0;
		// 	rdl_vars->curs_row_pos++;
		// 	clear_curr_line_after_cursor(rdl_vars);
		// }