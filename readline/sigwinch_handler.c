#include "readline.h"

void	detect_screen_resizing(t_rdline *rdl_vars)
{
	int		new_screen_width_size;

	new_screen_width_size = get_screen_width();
	rdl_vars->width_of_screen = new_screen_width_size;
	update_cursor_data(rdl_vars);
}

void	sigwinch_handler(int sig_num)
{
	if (sig_num == SIGWINCH)
		detect_screen_resizing(&g_vars.rdl_vars);
}
