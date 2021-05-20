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

void	start_key_action(t_rdline *rdl_vars, int key, char c)
{
	t_vchar_vec		*history_vec;

	history_vec = &rdl_vars->history_vec;
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
	else if (key == printable)
		print_curr_char(rdl_vars, c);
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
