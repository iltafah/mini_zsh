#include "readline.h"

static void		move_cursor_left_or_right(t_rdline *rdl_vars, int key)
{
	int				s_hilitd_col;
	int 			s_hilitd_row;

	s_hilitd_col = rdl_vars->starting_hilitd_colm;
	s_hilitd_row = rdl_vars->starting_hilitd_row;
	if (key == left_arrow)
	{
		if (rdl_vars->starting_hilitd_index < rdl_vars->curr_hilitd_char_index)
		{
			move_cursor_to_colum_and_row(rdl_vars, s_hilitd_col, s_hilitd_row);
			rdl_vars->c_i = rdl_vars->starting_hilitd_index;
		}
		
	}
	else if (key == right_arrow)
	{
		if (rdl_vars->curr_hilitd_char_index < rdl_vars->starting_hilitd_index)
		{
			move_cursor_to_colum_and_row(rdl_vars, s_hilitd_col, s_hilitd_row);
			rdl_vars->c_i = rdl_vars->starting_hilitd_index;
		}
	}
}

static void		move_curs_to_left_hilitd_pos(t_rdline *rdl_v, int *index)
{
	int				strt_hilitd_col;
	int 			strt_hilitd_row;

	strt_hilitd_col = rdl_v->starting_hilitd_colm;
	strt_hilitd_row = rdl_v->starting_hilitd_row;
	if (rdl_v->starting_hilitd_index > rdl_v->curr_hilitd_char_index)
		*index = rdl_v->curr_hilitd_char_index;
	else
	{
		*index = rdl_v->starting_hilitd_index;
		move_cursor_to_colum_and_row(rdl_v, strt_hilitd_col, strt_hilitd_row);
	}
}

void			turn_off_reverse_video_mode(t_rdline *rdl_vars, int key)
{
	t_vchar_vec		*history_vec;
	char			*hstry_str;
	int				higligtd_beg_i;

	if (rdl_vars->reverse_video_mode == 1)
	{
		history_vec = &rdl_vars->history_vec;
		hstry_str = history_vec->elements[rdl_vars->l_i].elements;
		save_curr_cursor_pos(rdl_vars);
		move_curs_to_left_hilitd_pos(rdl_vars, &higligtd_beg_i);
		tputs(tgetstr("ve", NULL), 1, put_char);
		tputs(tgetstr("se", NULL), 1, put_char);
		print_after_cursor(rdl_vars, hstry_str + higligtd_beg_i, dont_restore);
		restore_cursor_pos(rdl_vars);
		move_cursor_left_or_right(rdl_vars, key);
		rdl_vars->reverse_video_mode = 0;
	}
}

void			turn_on_reverse_video_mode(t_rdline *rdl_vars)
{
	t_vchar_vec		*history_vec;
	int				used_size;

	history_vec = &rdl_vars->history_vec;
	used_size = history_vec->elements[rdl_vars->l_i].used_size;
	if (rdl_vars->reverse_video_mode == 0)
	{
		tputs(tgetstr("vi", NULL), 1, put_char);
		rdl_vars->curr_hilitd_char_index = rdl_vars->c_i;
		rdl_vars->starting_hilitd_colm = rdl_vars->curs_colm_pos;
		rdl_vars->starting_hilitd_row = rdl_vars->curs_row_pos;
		rdl_vars->starting_hilitd_index = rdl_vars->c_i;
		rdl_vars->reverse_video_mode = 1;
	}
}
		// rdl_vars->hilitd_colm = rdl_vars->curs_colm_pos;
		// rdl_vars->hilitd_row = rdl_vars->curs_row_pos;
