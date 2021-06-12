#include "../readline.h"

void	start_enter_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, enter);
	insert_curr_line_to_history(rdl_vars);
	move_cursor_to_end_of_printed_line(rdl_vars);
	erase_suggestions(rdl_vars);
	put_char('\n');
}
