#include "../readline.h"

void	cut_highlighted_text(t_rdline *rdl_vars)
{
	int				beg;
	int				last;
	t_char_vec		*hstry_line;
	t_vchar_vec		*history_vec;
	int				chars_len_to_be_deleted;

	history_vec = &rdl_vars->history_vec;
	hstry_line = history_vec->elements;
	if (rdl_vars->reverse_video_mode == 1)
	{
		determine_beg_last_highlighted_txt_indx(rdl_vars);
		beg = rdl_vars->beg_hilitd_index;
		last = rdl_vars->last_hilitd_index;
		chars_len_to_be_deleted = last - beg;
		copy_highlighted_text(rdl_vars);
		while (chars_len_to_be_deleted)
		{
			hstry_line[rdl_vars->l_i].delete_element_at_index(hstry_line, beg);
			chars_len_to_be_deleted--;
		}
		clear_curr_line_after_and_below_cursor(rdl_vars);
		turn_off_reverse_video_mode(rdl_vars, ctl_x);
	}
}
