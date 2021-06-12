#include "../readline.h"

void	start_ctl_down_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, ctl_down_arrow);
	move_down_vertically(rdl_vars);
}
