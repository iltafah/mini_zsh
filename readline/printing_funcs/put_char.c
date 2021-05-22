#include "../readline.h"

int	put_char(int c)
{
	int	len;

	len = write(g_vars.rdl_vars.tty_fd, &c, 1);
	return (len);
}
