#include "./readline.h"

static void to_be_highlighted_or_not(t_rdline *rdl_v)
{
	if (rdl_v->curr_hilitd_char_index < rdl_v->c_i)
		tputs(tgetstr("se", NULL), 1, put_char);
	else
		tputs(tgetstr("so", NULL), 1, put_char);
}

void		right_highlight(t_rdline *rdl_v)
{
	t_vchar_vec		*hstry_vec;
	t_char_vec		*hstry_line;
	int				last_index;
	char			char_to_be_hilitd;

	hstry_vec = &rdl_v->history_vec;
	hstry_line = &hstry_vec->elements[rdl_v->l_i];
	char_to_be_hilitd = hstry_line->elements[rdl_v->curr_hilitd_char_index];
	last_index = hstry_vec->elements[rdl_v->l_i].last_index;
	save_curr_cursor_pos(rdl_v);
	move_cursor_to_colum_and_row(rdl_v, rdl_v->hilitd_colm, rdl_v->hilitd_row);
	if (rdl_v->curr_hilitd_char_index <= last_index)
	{
		to_be_highlighted_or_not(rdl_v);
		rdl_print_char(rdl_v, char_to_be_hilitd, WHT);
		rdl_v->curr_hilitd_char_index++;
		if (rdl_v->curs_colm_pos == rdl_v->width_of_screen)
			move_cursor_start_of_next_line(rdl_v);
		rdl_v->hilitd_colm = rdl_v->curs_colm_pos;
		rdl_v->hilitd_row = rdl_v->curs_row_pos;
	}
	restore_cursor_pos(rdl_v);
}