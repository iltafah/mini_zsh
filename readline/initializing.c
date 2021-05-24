#include "./readline.h"

void	initialize_tty_device(t_rdline *rdl_vars)
{
	int		std_fd;
	char	*tty_name;

	if (isatty(STDIN_FILENO))
		std_fd = STDIN_FILENO;
	else if (isatty(STDOUT_FILENO))
		std_fd = STDOUT_FILENO;
	else if (isatty(STDERR_FILENO))
		std_fd = STDERR_FILENO;
	tty_name = ttyname(std_fd);
	rdl_vars->tty_fd = open(tty_name, O_WRONLY);
}

void	initialize_termios_struct(struct termios *original_termios_state)
{
	char		*term_type;

	term_type = getenv("TERM");
	tgetent(NULL, term_type);
	tcgetattr(g_vars.rdl_vars.tty_fd, original_termios_state);
}

void	initialize_capabilities(t_capability *capability)
{
	capability->mv_cursor_up_vertically = tgetstr("up", NULL);
	capability->mv_cursor_down_vertically = tgetstr("do", NULL);
	capability->mv_cursor_left = tgetstr("le", NULL);
	capability->mv_cursor_right = tgetstr("nd", NULL);
	capability->mv_cursor_to_colm = tgetstr("ch", NULL);
	capability->clear_line_after_cursor = tgetstr("ce", NULL);
	capability->clear_lines_below = tgetstr("cd", NULL);
}

void	initialize_rdl_vars(t_rdline *rdl_vars)
{
	rdl_vars->key_seq_trie = initialize_key_seq_trie();
	initialize_tty_device(rdl_vars);
	initialize_vec_of_char_vec(&rdl_vars->history_vec);
	rdl_vars->c_i = 0;
	rdl_vars->l_i = 0;
	rdl_vars->curs_row_pos = 0;
	rdl_vars->curs_colm_pos = 0;
	rdl_vars->curs_row_old_pos = 0;
	rdl_vars->curs_colm_old_pos = 0;
	rdl_vars->prompt_len = 0;
	rdl_vars->printed_lines = 0;
	rdl_vars->width_of_screen = 0;
	rdl_vars->reverse_video_mode = 0;
	rdl_vars->reverse_video_mode = 0;
	rdl_vars->curr_hilitd_char_index = 0;
	// rdl_vars->hilitd_row = 0;
	// rdl_vars->hilitd_colm = 0;
	rdl_vars->hilitd_text = NULL;
	rdl_vars->line = NULL;
	rdl_vars->prompt = NULL;
	rdl_vars->old_history = NULL;
}
