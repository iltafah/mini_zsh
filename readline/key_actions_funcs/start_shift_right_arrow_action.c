#include "../readline.h"

void	start_shift_right_arrow_action(t_rdline *rdl_vars)
{
	start_highlighting_mode(rdl_vars);
	right_highlight(rdl_vars);
}
