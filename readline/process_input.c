#include	"readline.h"

void	set_rdl_vars(t_rdline *rdl_vars, char *prompt)
{
	t_vchar_vec		*history_vec;
	t_char_vec		*history_line;

	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	rdl_vars->old_history = convert_history_vec_to_array(history_vec);
	add_empty_char_vec_to_history_vec(history_vec);
	rdl_vars->prompt = prompt;
	rdl_vars->prompt_len = ft_strlen_utf8(rdl_vars->prompt);
	rdl_vars->width_of_screen = get_screen_width();
	rdl_vars->c_i = 0;
	rdl_vars->l_i = history_vec->last_index;
	rdl_vars->curs_row_pos = 0;
	rdl_vars->curs_colm_pos = rdl_vars->prompt_len;
}

void	start_key_action(t_rdline *rdl_vars, int key, char c)
{
	if (key == shift_left_arrow || key == shift_right_arrow)
		start_highlighting_mode(rdl_vars);
	else if (key != ctl_s && key != ctl_x)
		quit_highlighting_mode(rdl_vars, key);

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
	else if (key == shift_left_arrow)
		left_highlight(rdl_vars);
	else if (key == shift_right_arrow)
		right_highlight(rdl_vars);
	else if (key == ctl_up_arrow)
		move_up_vertically(rdl_vars);
	else if (key == ctl_down_arrow)
		move_down_vertically(rdl_vars);
	else if (key == ctl_right_arrow)
		move_to_next_word(rdl_vars);
	else if (key == ctl_left_arrow)
		move_to_prec_word(rdl_vars);
	else if (key == ctl_s)
		copy_highlighted_text(rdl_vars);
	else if (key == ctl_v)
		past_highlighted_text(rdl_vars);
	else if (key == ctl_x)
		cut_highlighted_text(rdl_vars);
	else if (key == enter)
	{
		insert_curr_line_to_history(rdl_vars);
		erase_suggestions(rdl_vars);
		put_char('\n');
	}
	fprintf(fd, "======================================================\n");
	fprintf(fd, "curs_pos (%d, %d)\n", rdl_vars->curs_colm_pos, rdl_vars->curs_row_pos);
	fprintf(fd, "c_i : (%d) , l_i : (%d)\n", rdl_vars->c_i, rdl_vars->l_i);
	fprintf(fd, "printed_lines : (%d)\n", rdl_vars->printed_lines);
	fflush(fd);
	// fprintf(fd2, "======================================================\n");
	// fflush(fd2);
}

void	process_input(t_rdline *rdl_vars, char *prompt)
{
	int		key;
	char	c;
/////////////////////
fd = fopen("./debug.txt", "w+");
fd2 = fopen("debug2.txt", "w+");
/////////////////////
	key = none;
	set_rdl_vars(rdl_vars, prompt);
	print_prompt(rdl_vars);
	while (read(STDIN_FILENO, &c, 1))
	{
		key = get_key(rdl_vars->key_seq_trie, c);
		if (key == none || key == waiting)
			SKIP ;
		start_key_action(rdl_vars, key, c);
		if (key == enter)
			break ;
	}
	free_array(&rdl_vars->old_history);
}
