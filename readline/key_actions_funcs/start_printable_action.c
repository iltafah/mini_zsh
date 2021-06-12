#include "../readline.h"

void	start_printable_action(t_rdline *rdl_vars, char c)
{
	quit_highlighting_mode(rdl_vars, printable);
	print_curr_char(rdl_vars, c);
}
