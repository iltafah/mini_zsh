#include "../readline.h"

void	start_down_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, down_arrow);
	show_new_history(rdl_vars);
}
