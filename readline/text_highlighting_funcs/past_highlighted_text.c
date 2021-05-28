#include "../readline.h"

void	past_highlighted_text(t_rdline *rdl_vars)
{
	t_vchar_vec		*hstry_vec;
	t_char_vec		*hstry_line;
	char			*hstry_str;
	int				line_i;
	int				char_i;

	if (rdl_vars->hilitd_txt != NULL)
	{
		hstry_vec = &rdl_vars->history_vec;
		hstry_line = hstry_vec->elements;
		line_i = rdl_vars->l_i;
		char_i = rdl_vars->c_i;
		hstry_line[line_i].add_set_of_elements_at_index(&hstry_line[line_i],
			rdl_vars->hilitd_txt, char_i);
		hstry_str = hstry_line[rdl_vars->l_i].elements;
		print_after_cursor(rdl_vars, hstry_str + char_i, restore);
		print_suggestions(rdl_vars);
	}
}
