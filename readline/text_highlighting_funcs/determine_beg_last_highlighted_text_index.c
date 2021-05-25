#include "../readline.h"

void	determine_beg_last_highlighted_txt_indx(t_rdline *rdl_v)
{
	if (rdl_v->starting_hilitd_index < rdl_v->curr_hilitd_char_index)
	{
		rdl_v->beg_hilitd_index = rdl_v->starting_hilitd_index;
		rdl_v->last_hilitd_index = rdl_v->curr_hilitd_char_index;
	}
	else
	{
		rdl_v->beg_hilitd_index = rdl_v->curr_hilitd_char_index;
		rdl_v->last_hilitd_index = rdl_v->starting_hilitd_index;
	}
}
