#include "../readline.h"

void	start_end_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, end);
	move_to_end_of_line(rdl_vars);
}
