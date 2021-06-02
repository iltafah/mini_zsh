#include "readline.h"

void	signals_handler(int sig_num)
{
	if (sig_num == SIGWINCH)
		detect_screen_resizing(&g_vars.rdl_vars);
	else if (sig_num == SIGINT)
	{
		// overwrite_history_file(&g_vars.rdl_vars);
		disable_raw_mode(g_vars.rdl_vars.original_termios_state);
		exit(130);
	}
}
