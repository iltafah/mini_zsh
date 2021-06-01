#include "../readline.h"

void	print_line_with_chosen_method(t_rdline *rdl_vrs, char *line, int option)
{
	if (rdl_vrs->syntax_highlighting == on)
		print_with_syntax_highlighting(rdl_vrs, option);
	else
		print_after_cursor(rdl_vrs, line, option);
}
