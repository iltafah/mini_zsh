#include "../readline.h"

void	start_backspace_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, backspace);
	erase_and_remove_curr_char(rdl_vars);
}
