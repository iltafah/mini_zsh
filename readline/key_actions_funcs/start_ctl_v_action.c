#include "../readline.h"

void	start_ctl_v_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, ctl_v);
	past_highlighted_text(rdl_vars);
}
