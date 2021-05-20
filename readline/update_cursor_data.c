#include "readline.h"

void	update_cursor_data(t_rdline *rdl_vars)
{
	int			l_i;
	int			printed_chars;
	int			prntd_chrs_bef_curs;
	t_vchar_vec	*history_vec;
	t_char_vec	*history_line;

	l_i = rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	prntd_chrs_bef_curs = rdl_vars->prompt_len + rdl_vars->c_i;
	printed_chars = rdl_vars->prompt_len + history_line[l_i].last_index;
	rdl_vars->printed_lines = (printed_chars) / rdl_vars->width_of_screen + 1;
	rdl_vars->curs_row_pos = (prntd_chrs_bef_curs) / rdl_vars->width_of_screen;
	rdl_vars->curs_colm_pos = (prntd_chrs_bef_curs) % rdl_vars->width_of_screen;
}
