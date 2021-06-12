#include "../readline.h"

void	start_ctl_left_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, ctl_left_arrow);
	move_to_prec_word(rdl_vars);
}
