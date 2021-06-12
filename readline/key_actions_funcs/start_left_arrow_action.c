#include "../readline.h"

void	start_left_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, left_arrow);
	move_left(rdl_vars);
}
