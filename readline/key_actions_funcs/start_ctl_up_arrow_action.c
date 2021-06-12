#include "../readline.h"

void	start_ctl_up_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, ctl_up_arrow);
	move_up_vertically(rdl_vars);
}
