#include "readline.h"

int	get_screen_width(void)
{
	struct winsize	window;

	ioctl(g_vars.rdl_vars.tty_fd, TIOCGWINSZ, &window);
	return (window.ws_col);
}
