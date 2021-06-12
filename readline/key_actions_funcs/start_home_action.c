#include "../readline.h"

void	start_home_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, home);
	show_old_history(rdl_vars);
}
