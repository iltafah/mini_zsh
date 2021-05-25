#include "../readline.h"

void	past_highlighted_text(t_rdline *rdl_vars)
{
	t_vchar_vec		*hstry_vec;
	t_char_vec		*hstry_line;
	char			*hstry_str;
	char			*copied_txt;
	int				curr_index;

	if (rdl_vars->hilitd_txt != NULL)
	{
		hstry_vec = &rdl_vars->history_vec;
		hstry_line = hstry_vec->elements;
		curr_index = rdl_vars->c_i;
		copied_txt = rdl_vars->hilitd_txt;
		hstry_line->add_set_of_elements_at_index(hstry_line, copied_txt,
			curr_index);
		hstry_str = hstry_line[rdl_vars->l_i].elements;
		print_after_cursor(rdl_vars, hstry_str + curr_index, restore);
	}
}
