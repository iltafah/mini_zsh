#include "../readline.h"

void	move_cursor_to_end_of_printed_line(t_rdline *rdl_vars)
{
	t_vchar_vec	*history_vec;
	t_char_vec	*history_line;
	int			printed_chars;
	int			l_i;
	int			col_to_move;
	int			row_to_move;

	l_i = rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	printed_chars = rdl_vars->prompt_len + history_line[l_i].last_index;
	if (history_line[l_i].used_size > 0)
	{
		col_to_move = (printed_chars) / rdl_vars->width_of_screen;
		row_to_move = (printed_chars) % rdl_vars->width_of_screen;
		move_cursor_to_colum_and_row(rdl_vars, col_to_move, row_to_move);
	}
}

void	print_suggestions(t_rdline *rdl_vars)
{
	t_vchar_vec		*hstry_vec;
	t_char_vec		*hstry_line;
	int				curr_line_index;
	int				l_i;

	hstry_vec = &rdl_vars->history_vec;
	hstry_line = hstry_vec->elements;
	l_i = rdl_vars->l_i;
//////////////////////////////////////////
save_curr_cursor_pos(rdl_vars);
move_cursor_to_end_of_printed_line(rdl_vars);
//////////////////////////////////////////
	clear_curr_line_after_and_below_cursor(rdl_vars);
	if (l_i > 0 && hstry_line[l_i].used_size > 0)
	{
		curr_line_index = l_i - 1;
		while (curr_line_index >= 0)
		{
			if (ft_strncmp(hstry_line[l_i].elements,
				hstry_line[curr_line_index].elements,
				hstry_line[l_i].used_size) == 0)
			{
				int		i;

				i = hstry_line[l_i].last_index + 1;
				while (i < hstry_line[curr_line_index].used_size)
				{
					rdl_print_char(rdl_vars, hstry_line[curr_line_index].elements[i], GRY);
					i++;
				}
				break ;
			}
			curr_line_index--;
		}
	}
/////////////////////////////
restore_cursor_pos(rdl_vars);
/////////////////////////////
}
