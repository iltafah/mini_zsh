#include "../readline.h"

void	start_ctl_right_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, ctl_right_arrow);
	move_to_next_word(rdl_vars);
}
