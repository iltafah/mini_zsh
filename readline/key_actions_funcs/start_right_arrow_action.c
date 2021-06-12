#include "../readline.h"

void	start_right_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, right_arrow);
	move_right(rdl_vars);
}
