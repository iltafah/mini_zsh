#include "../readline.h"

void	start_shift_left_arrow_action(t_rdline *rdl_vars)
{
	start_highlighting_mode(rdl_vars);
	left_highlight(rdl_vars);
}
