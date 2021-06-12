#include "../readline.h"

void	start_highlighting_mode(t_rdline *rdl_vars)
{
	t_vchar_vec		*history_vec;
	int				used_size;

	history_vec = &rdl_vars->history_vec;
	used_size = history_vec->elements[rdl_vars->l_i].used_size;
	if (rdl_vars->reverse_video_mode == 0)
	{
		tputs(rdl_vars->capability.make_cursor_invisible, 1, put_char);
		rdl_vars->curr_hilitd_char_index = rdl_vars->c_i;
		rdl_vars->starting_hilitd_colm = rdl_vars->curs_colm_pos;
		rdl_vars->starting_hilitd_row = rdl_vars->curs_row_pos;
		rdl_vars->starting_hilitd_index = rdl_vars->c_i;
		rdl_vars->reverse_video_mode = 1;
	}
}
