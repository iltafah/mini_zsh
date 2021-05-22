#include	"readline.h"

void	set_rdl_vars(t_rdline *rdl_vars)
{
	t_vchar_vec		*history_vec;
	t_char_vec		*history_line;

	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	rdl_vars->old_history = convert_history_vec_to_array(history_vec);
	add_empty_char_vec_to_history_vec(history_vec);
	rdl_vars->prompt = get_prompt_name();
	rdl_vars->prompt_len = ft_strlen_utf8(rdl_vars->prompt);
	rdl_vars->width_of_screen = get_screen_width();
	rdl_vars->c_i = 0;
	rdl_vars->l_i = history_vec->last_index;
	rdl_vars->curs_row_pos = 0;
	rdl_vars->curs_colm_pos = rdl_vars->prompt_len;
	rdl_vars->curs_row_old_pos = 0;
	rdl_vars->curs_colm_old_pos = 0;
}

void	left_highlight(t_rdline *rdl_vars)
{
	t_vchar_vec		*history_vec;
	t_char_vec		*history_line;

	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	save_curr_cursor_pos(rdl_vars);
	
	if (rdl_vars->curr_highlighted_char_index >= 0)
	{
		move_cursor_to_colum_and_row(rdl_vars, rdl_vars->highlight_colm_pos, rdl_vars->highlight_row_pos);

		if (rdl_vars->curr_highlighted_char_index > rdl_vars->c_i)
			tputs(tgetstr("me", NULL), 1, put_char);
		else
			tputs(tgetstr("mr", NULL), 1, put_char);

		// tputs(tgetstr("dc", NULL), 1, put_char);
		// tputs(tgetstr("ic", NULL), 1, put_char);
		put_char(history_line[rdl_vars->l_i].elements[rdl_vars->curr_highlighted_char_index]);
		rdl_vars->curr_highlighted_char_index--;
		// tputs(tgetstr("ip", NULL), 1, put_char);
		if (rdl_vars->curs_colm_pos > 0)
			move_cursor_left(rdl_vars);
		else
			move_cursor_end_of_prec_line(rdl_vars);
		rdl_vars->highlight_colm_pos = rdl_vars->curs_colm_pos;
		rdl_vars->highlight_row_pos = rdl_vars->curs_row_pos;
	}
	restore_cursor_pos(rdl_vars);
}

void	right_highlight(t_rdline *rdl_vars)
{
	t_vchar_vec		*history_vec;
	t_char_vec		*history_line;

	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;

	save_curr_cursor_pos(rdl_vars);
	
	if (rdl_vars->curr_highlighted_char_index <= history_line[rdl_vars->l_i].last_index)
	{
		move_cursor_to_colum_and_row(rdl_vars, rdl_vars->highlight_colm_pos, rdl_vars->highlight_row_pos);
		

		if (rdl_vars->curr_highlighted_char_index < rdl_vars->c_i)
			tputs(tgetstr("me", NULL), 1, put_char);
		else
			tputs(tgetstr("mr", NULL), 1, put_char);
		// tputs(tgetstr("dc", NULL), 1, put_char);
		// tputs(tgetstr("ic", NULL), 1, put_char);
		put_char(history_line[rdl_vars->l_i].elements[rdl_vars->curr_highlighted_char_index]);
		rdl_vars->curr_highlighted_char_index++;
		// tputs(tgetstr("ip", NULL), 1, put_char);
		if (rdl_vars->curs_colm_pos < rdl_vars->width_of_screen - 1)
			move_cursor_right(rdl_vars);
		else
			move_cursor_start_of_next_line(rdl_vars);
		rdl_vars->highlight_colm_pos = rdl_vars->curs_colm_pos;
		rdl_vars->highlight_row_pos = rdl_vars->curs_row_pos;
	}
	restore_cursor_pos(rdl_vars);
}

void	turn_on_reverse_video_mode(t_rdline *rdl_vars)
{
	t_vchar_vec		*history_vec;
	int				used_size;

	history_vec = &rdl_vars->history_vec;
	used_size = history_vec->elements[rdl_vars->l_i].used_size;
	if (rdl_vars->reverse_video_mode == 0)
	{
		tputs(tgetstr("mr", NULL), 1, put_char);
		rdl_vars->highlight_colm_pos = rdl_vars->curs_colm_pos;
		rdl_vars->highlight_row_pos = rdl_vars->curs_row_pos;
		rdl_vars->curr_highlighted_char_index = rdl_vars->c_i;
		rdl_vars->reverse_video_mode = 1;
	}
}
void	turn_off_reverse_video_mode(t_rdline *rdl_vars)
{
	t_vchar_vec		*history_vec;
	char			*hstry_str;
	int				highlight_colm;
	int 			highlight_row;
	int 			highlighted_i;

	if (rdl_vars->reverse_video_mode == 1)
	{
		history_vec = &rdl_vars->history_vec;
		hstry_str = history_vec->elements[rdl_vars->l_i].elements;
		highlight_colm = rdl_vars->highlight_colm_pos;
		highlight_row = rdl_vars->highlight_row_pos;
		if (rdl_vars->curr_highlighted_char_index < rdl_vars->c_i)
		{
			rdl_vars->c_i = rdl_vars->curr_highlighted_char_index;
			move_cursor_to_colum_and_row(rdl_vars, highlight_colm, highlight_row);
		}
		save_curr_cursor_pos(rdl_vars);
		tputs(tgetstr("me", NULL), 1, put_char);
		print_after_cursor(rdl_vars, hstry_str + rdl_vars->c_i, restore);
		restore_cursor_pos(rdl_vars);
		rdl_vars->reverse_video_mode = 0;
	}
}

void	start_key_action(t_rdline *rdl_vars, int key, char c)
{
	if (key == shift_left_arrow || key == shift_right_arrow)
		turn_on_reverse_video_mode(rdl_vars);
	else
		turn_off_reverse_video_mode(rdl_vars);

	if (key == up_arrow)
		show_old_history(rdl_vars);
	else if (key == down_arrow)
		show_new_history(rdl_vars);
	else if (key == left_arrow)
		move_left(rdl_vars);
	else if (key == right_arrow)
		move_right(rdl_vars);
	else if (key == backspace)
		erase_and_remove_curr_char(rdl_vars);
	else if (key == home)
		move_to_beginning_of_line(rdl_vars);
	else if (key == end)
		move_to_end_of_line(rdl_vars);
	else if (key == printable)
		print_curr_char(rdl_vars, c);
	else if (key == alt_up_arrow)
		move_up_vertically(rdl_vars);
	else if (key == alt_down_arrow)
		move_down_vertically(rdl_vars);
	else if (key == alt_right_arrow)
		move_to_next_word(rdl_vars);
	else if (key == alt_left_arrow)
		move_to_prec_word(rdl_vars);
	else if (key == shift_left_arrow)
		left_highlight(rdl_vars);
	else if (key == shift_right_arrow)
		right_highlight(rdl_vars);
	else if (key == enter)
	{
		insert_curr_line_to_history(rdl_vars);
		put_char('\n');
	}
}

void	process_input(char **line, t_rdline *rdl_vars)
{
	int		key;
	char	c;

	key = none;
	set_rdl_vars(rdl_vars);
	signal(SIGWINCH, sigwinch_handler);
	print_prompt(rdl_vars);
	while (read(STDIN_FILENO, &c, 1))
	{
		key = get_key(rdl_vars->key_seq_trie, c);
		if (key == waiting)
			continue ;
		start_key_action(rdl_vars, key, c);
		if (key == enter)
			break ;
	}
	*line = rdl_vars->line;
	free_array(&rdl_vars->old_history);
	free(rdl_vars->prompt);
}
