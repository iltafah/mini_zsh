#include "../readline.h"

static void		delete_hilitd_chars_from_history_line(t_rdline *rdl_vars)
{
	t_char_vec		*hstry_line;
	t_vchar_vec		*history_vec;
	int				line_i;
	int				chars_len_to_be_deleted;

	history_vec = &rdl_vars->history_vec;
	hstry_line = history_vec->elements;
	line_i = rdl_vars->l_i;
	chars_len_to_be_deleted = rdl_vars->last_hilitd_index
		- rdl_vars->beg_hilitd_index;
	while (chars_len_to_be_deleted)
	{
		hstry_line[line_i].delete_element_at_index(&hstry_line[line_i],
		rdl_vars->beg_hilitd_index);
		chars_len_to_be_deleted--;
	}
}              

void			cut_highlighted_text(t_rdline *rdl_vars)
{
	int				chars_len_to_be_deleted;

	if (rdl_vars->reverse_video_mode == 1)
	{
		determine_beg_last_highlighted_txt_indx(rdl_vars);
		copy_highlighted_text(rdl_vars);
		delete_hilitd_chars_from_history_line(rdl_vars);
		clear_curr_line_after_and_below_cursor(rdl_vars);
		turn_off_reverse_video_mode(rdl_vars, ctl_x);
	}
}
