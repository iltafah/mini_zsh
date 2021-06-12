#include "../readline.h"

void	start_up_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, up_arrow);
	show_old_history(rdl_vars);
}
