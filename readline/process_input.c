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

// void	turn_on_reverse_video_mode(t_rdline *rdl_vars)
// {
// 	t_vchar_vec		*history_vec;
// 	int				used_size;

// 	history_vec = &rdl_vars->history_vec;
// 	used_size = history_vec->elements[rdl_vars->l_i].used_size;
// 	if (rdl_vars->reverse_video_mode == 0)
// 	{
// 		tputs(tgetstr("vi", NULL), 1, put_char);
// 		rdl_vars->hilitd_colm = rdl_vars->curs_colm_pos;
// 		rdl_vars->hilitd_row = rdl_vars->curs_row_pos;
// 		rdl_vars->curr_hilitd_char_index = rdl_vars->c_i;
// 		rdl_vars->reverse_video_mode = 1;
// 	}
// }

// void	turn_off_reverse_video_mode(t_rdline *rdl_vars, int key)
// {
// 	t_vchar_vec		*history_vec;
// 	char			*hstry_str;
// 	int				hilitd_colm;
// 	int 			hilitd_row;
// 	int 			hilitded_i;
// 	int				higligtd_beg_i;

// 	if (rdl_vars->reverse_video_mode == 1)
// 	{
// 		history_vec = &rdl_vars->history_vec;
// 		hstry_str = history_vec->elements[rdl_vars->l_i].elements;
// 		hilitd_colm = rdl_vars->hilitd_colm;
// 		hilitd_row = rdl_vars->hilitd_row;
// 		save_curr_cursor_pos(rdl_vars);
// 		if (rdl_vars->curr_hilitd_char_index > rdl_vars->c_i)
// 			higligtd_beg_i = rdl_vars->c_i;
// 		else
// 		{
// 			higligtd_beg_i = rdl_vars->curr_hilitd_char_index;
// 			move_cursor_to_colum_and_row(rdl_vars, hilitd_colm, hilitd_row);
// 		}
// 		tputs(tgetstr("ve", NULL), 1, put_char);
// 		tputs(tgetstr("se", NULL), 1, put_char);
// 		print_after_cursor(rdl_vars, hstry_str + higligtd_beg_i, dont_restore);
// 		restore_cursor_pos(rdl_vars);

// 		if (key == left_arrow)
// 		{
// 			if (rdl_vars->curr_hilitd_char_index < rdl_vars->c_i)
// 			{
// 				move_cursor_to_colum_and_row(rdl_vars, hilitd_colm, hilitd_row);
// 				rdl_vars->c_i = rdl_vars->curr_hilitd_char_index;
// 			}
// 		}
// 		else if (key == right_arrow)
// 		{
// 			if (rdl_vars->curr_hilitd_char_index > rdl_vars->c_i)
// 			{
// 				move_cursor_to_colum_and_row(rdl_vars, hilitd_colm, hilitd_row);
// 				rdl_vars->c_i = rdl_vars->curr_hilitd_char_index;
// 			}
// 		}
// 		rdl_vars->reverse_video_mode = 0;
// 	}
// }

void	copy_highlighted_text(t_rdline *rdl_vars)
{
	t_vchar_vec		*history_vec;
	char			*hstry_str;
	int		beg_hilitd_text_index;
	int		last_hilitd_text_index;
	int		hilitd_text_len;
	int		i;

if (rdl_vars->reverse_video_mode == 1)
{
	history_vec = &rdl_vars->history_vec;
	hstry_str = history_vec->elements[rdl_vars->l_i].elements;

	if (rdl_vars->hilitd_text != NULL)
		free(rdl_vars->hilitd_text);

	if (rdl_vars->starting_hilitd_index < rdl_vars->curr_hilitd_char_index)
	{
		beg_hilitd_text_index = rdl_vars->starting_hilitd_index;
		last_hilitd_text_index = rdl_vars->curr_hilitd_char_index;
	}
	else
	{
		beg_hilitd_text_index = rdl_vars->curr_hilitd_char_index;
		last_hilitd_text_index = rdl_vars->starting_hilitd_index;
	}

	hilitd_text_len = last_hilitd_text_index - beg_hilitd_text_index;
	rdl_vars->hilitd_text = malloc(sizeof(char) * (hilitd_text_len + 1));
	i = 0;
	while (beg_hilitd_text_index < last_hilitd_text_index)
	{
		rdl_vars->hilitd_text[i] = hstry_str[beg_hilitd_text_index];
		beg_hilitd_text_index++;
		i++;
	}
	rdl_vars->hilitd_text[i] = '\0';
}
}

void	past_highlighted_text(t_rdline *rdl_vars)
{
	t_vchar_vec		*hstry_vec;
	t_char_vec		*hstry_line;
	char			*hstry_str;
	char			*cpid_txt;
	int				curr_i;

	if (rdl_vars->hilitd_text != NULL)
	{
		hstry_vec = &rdl_vars->history_vec;
		hstry_line = hstry_vec->elements;
		curr_i = rdl_vars->c_i;
		cpid_txt = rdl_vars->hilitd_text;
		hstry_line->add_set_of_elements_at_index(hstry_line, cpid_txt, curr_i);
		hstry_str = hstry_line[rdl_vars->l_i].elements;
		print_after_cursor(rdl_vars, hstry_str + curr_i, restore);
	}
}

void	cut_highlighted_text(t_rdline *rdl_vars)
{
	t_vchar_vec		*history_vec;
	t_char_vec *hstry_line;
	char			*hstry_str;
	int		beg_hilitd_text_index;
	int		last_hilitd_text_index;
	int		hilitd_text_len;
	int		i;

	history_vec = &rdl_vars->history_vec;
	hstry_line = history_vec->elements;
	
	if (rdl_vars->starting_hilitd_index < rdl_vars->curr_hilitd_char_index)
	{
		beg_hilitd_text_index = rdl_vars->starting_hilitd_index;
		last_hilitd_text_index = rdl_vars->curr_hilitd_char_index;
	}
	else
	{
		beg_hilitd_text_index = rdl_vars->curr_hilitd_char_index;
		last_hilitd_text_index = rdl_vars->starting_hilitd_index;
	}
	
	i = beg_hilitd_text_index;
	if (rdl_vars->reverse_video_mode == 1)
	{
		copy_highlighted_text(rdl_vars);
		while (i < last_hilitd_text_index)
		{
			hstry_line[rdl_vars->l_i].delete_element_at_index(hstry_line, beg_hilitd_text_index);
			i++;
		}
		save_curr_cursor_pos(rdl_vars);
		if (rdl_vars->starting_hilitd_index < rdl_vars->curr_hilitd_char_index)
		{
			move_cursor_to_colum_and_row(rdl_vars, rdl_vars->starting_hilitd_colm, rdl_vars->starting_hilitd_row);
		}
		tputs(tgetstr("se", NULL), 1, put_char);
		print_after_cursor(rdl_vars, hstry_line[rdl_vars->l_i].elements + beg_hilitd_text_index, dont_restore);
		restore_cursor_pos(rdl_vars);
	}
}

void	start_key_action(t_rdline *rdl_vars, int key, char c)
{
	if (key == shift_left_arrow || key == shift_right_arrow)
		turn_on_reverse_video_mode(rdl_vars);
	else if (key != ctl_s && key != ctl_x)
		turn_off_reverse_video_mode(rdl_vars, key);

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
	else if (key == ctl_up_arrow)
		move_up_vertically(rdl_vars);
	else if (key == ctl_down_arrow)
		move_down_vertically(rdl_vars);
	else if (key == ctl_right_arrow)
		move_to_next_word(rdl_vars);
	else if (key == ctl_left_arrow)
		move_to_prec_word(rdl_vars);
	else if (key == shift_left_arrow)
		left_highlight(rdl_vars);
	else if (key == shift_right_arrow)
		right_highlight(rdl_vars);
	else if (key == ctl_s)
		copy_highlighted_text(rdl_vars);
	else if (key == ctl_v)
		past_highlighted_text(rdl_vars);
	else if (key == ctl_x)
		cut_highlighted_text(rdl_vars);
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
/////////////////////
fd = fopen("./debug.txt", "w+");
/////////////////////
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
