#include "../readline.h"

void	move_cursor_to_end_of_printed_line(t_rdline *rdl_vars)
{
	t_vchar_vec	*history_vec;
	t_char_vec	*history_line;
	int			printed_chars;
	int			col_to_move;
	int			row_to_move;

	history_vec = &rdl_vars->history_vec;
	history_line = &history_vec->elements[rdl_vars->l_i];
	printed_chars = rdl_vars->prompt_len + history_line->used_size;
	if (history_line->used_size > 0)
	{
		col_to_move = printed_chars % rdl_vars->width_of_screen;
		row_to_move = printed_chars / rdl_vars->width_of_screen;
		fprintf(fd2, "pos_to_move : (%d, %d)\n" ,col_to_move, row_to_move);
		fflush(fd2);
		move_cursor_to_colum_and_row(rdl_vars, col_to_move, row_to_move);
	}
}
