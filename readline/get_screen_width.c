#include "readline.h"

int	get_screen_width(void)
{
	struct winsize	window;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &window);
	return (window.ws_col);
}
