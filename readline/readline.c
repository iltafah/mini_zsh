#include <ctype.h>
#include <termcap.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./readline.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// {
// 	size_t	dst_len;
// 	size_t	src_len;
// 	size_t	i;

// 	src_len = ft_strlen(src);
// 	if (!size)
// 		return (src_len);
// 	dst_len = ft_strlen(dst);
// 	i = dst_len;
// 	if (size < dst_len)
// 		return (src_len + size);
// 	while (i + 1 < size && *src)
// 		dst[i++] = *src++;
// 	if (size)
// 		dst[i] = '\0';
// 	return (dst_len + src_len);
// }

// size_t	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	src_len;
// 	size_t	i;

// 	src_len = ft_strlen(src);
// 	i = 0;
// 	while (i + 1 < size && src[i])
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	if (size)
// 		dst[i] = '\0';
// 	return (src_len);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t len;

// 	len = 0;
// 	while (*s++)
// 		len++;
// 	return (len);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t	s1_len;
// 	size_t	s2_len;
// 	size_t	total;
// 	char	*str;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	total = s1_len + s2_len + 1;
// 	if (!(str = malloc(sizeof(char) * total)))
// 		return (NULL);
// 	ft_strlcpy(str, s1, s1_len + 1);
// 	ft_strlcat(str, s2, total);
// 	return (str);
// }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ft_strlen_utf8(char *s) 
{
  int i = 0, j = 0;
  while (s[i]) 
  {
    if ((s[i] & 0xc0) != 0x80) j++;
    i++;
  }
  return j;
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int		put_char(int c)
{
	int		len;

	len = write(1, &c, 1);
	return (len);
}

char	*get_curr_dir_name()
{
	char *curr_dir;
	int keep_index;
	int len;
	int i;

	i = 0;
	len = 0;
	keep_index = 0;
	curr_dir = getcwd(NULL, 0);
	while (curr_dir[i] != '\0')
	{
		if (curr_dir[i] == '/')
			keep_index = i + 1;
		i++;
	}
	return (curr_dir + keep_index);
}

char	*get_prompt_name()
{
	static char arrow[] = "➜  ";
	static char	spaces[] = " ";
	char	*curr_dir;
	char	*tmp_ptr;
	char	*prompt;

	curr_dir = get_curr_dir_name();
	prompt = ft_strjoin(arrow, curr_dir);
	tmp_ptr = ft_strjoin(prompt, spaces);
	free(prompt);
	prompt = tmp_ptr;
	return (prompt);
}

void	print_prompt(t_rdline *rdl_vars)
{
	int		i;
	char	*prompt;

	i = 0;
	prompt = rdl_vars->prompt;
	write(1, GRN, ft_strlen(GRN));
	while (prompt[i] != ' ')
		put_char(prompt[i++]);
	write(1, CYN, ft_strlen(CYN));
	while (prompt[i] != '\0')
		put_char(prompt[i++]);
	write(1, WHT, ft_strlen(WHT));
}

// void	move_cursor_up_vetically(t_capability capability)
// {
// 	tputs(capability.mv_cursor_up_vertically, 1, put_char);
// }

void	move_cursor_to_colum(t_rdline *rdl_vars, int col)
{
	char	*ch_cap = tgetstr("ch", NULL);
	tputs(tgoto(ch_cap, 0, col), 1, put_char);
	rdl_vars->curs_colm_pos = col;
}


void	move_cursor_up_vertically(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_up_vertically, 1, put_char);
	rdl_vars->curs_row_pos--;
}

void	move_cursor_down_vertically(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_down_vertically, 1, put_char);
	rdl_vars->curs_row_pos++;
}

void	move_cursor_start_of_next_line(t_rdline *rdl_vars)
{
	move_cursor_to_colum(rdl_vars, 0);
	move_cursor_down_vertically(rdl_vars);
}

void	move_cursor_end_of_prec_line(t_rdline *rdl_vars)
{
	move_cursor_up_vertically(rdl_vars);
	move_cursor_to_colum(rdl_vars, rdl_vars->width_of_screen - 1);
}

void	move_cursor_right(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_right, 1, put_char);
	rdl_vars->curs_colm_pos++;
}

void	move_cursor_left(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_left, 1, put_char);
	rdl_vars->curs_colm_pos--;
}

int		get_screen_width()
{
	struct winsize w;
	
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

void	clear_curr_line_after_cursor(t_rdline *rdl_vars)
{
	move_cursor_to_colum(rdl_vars, rdl_vars->curs_colm_pos);
	tputs(rdl_vars->capability.clear_line_after_cursor, 1, put_char);
}

// void	clear_curr_line(t_rdline *rdl_vars)
// {
// 	rdl_vars->curs_colm_pos = 0;
// 	move_cursor_to_colum(rdl_vars, rdl_vars->curs_colm_pos);
// 	char	*clear_after_cursor = tgetstr("ce", NULL);
// 	tputs(clear_after_cursor, 1, put_char);
// }

void	clear_lines_below_cursor(t_rdline *rdl_vars)
{
	move_cursor_to_colum(rdl_vars, 0);
	tputs(rdl_vars->capability.clear_lines_below, 1, put_char);
}

// void	clear_lines_after_and_below_cursor(t_rdline *vars)
// {
// 	clear_curr_line_after_cursor(vars->curs_colm_pos);
// 	if (vars->curs_row_pos < vars->printed_lines)
// 	{
// 		move_cursor_start_of_next_line(vars->capability);
// 		clear_lines_below_cursor(vars->capability);
// 	}
// }

void	update_cursor_data(t_rdline *rdl_vars)
{
	int			l_i;
	int			printed_chars;
	int			prntd_chrs_bef_curs;
	t_vchar_vec	*history_vec;
	t_char_vec	*history_line;

	l_i = rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	prntd_chrs_bef_curs = rdl_vars->prompt_len + rdl_vars->c_i;
	printed_chars = rdl_vars->prompt_len + history_line[l_i].last_index;
	rdl_vars->printed_lines = (printed_chars) / rdl_vars->width_of_screen + 1;
	rdl_vars->curs_row_pos = (prntd_chrs_bef_curs) / rdl_vars->width_of_screen;
	rdl_vars->curs_colm_pos = (prntd_chrs_bef_curs) % rdl_vars->width_of_screen;
}

void	restore_cursor_pos(t_rdline *rdl_vars)
{
	while (rdl_vars->curs_row_pos > rdl_vars->curs_row_old_pos)
		move_cursor_up_vertically(rdl_vars);
	move_cursor_to_colum(rdl_vars, rdl_vars->curs_colm_old_pos);
}

void	save_curr_cursor_pos(t_rdline *rdl_vars)
{
	rdl_vars->curs_row_old_pos = rdl_vars->curs_row_pos;
	rdl_vars->curs_colm_old_pos = rdl_vars->curs_colm_pos;
}

void	clear_printed_lines(t_rdline *rdl_vars, int option)
{
	save_curr_cursor_pos(rdl_vars);
	while (rdl_vars->curs_row_pos > 0)
		move_cursor_up_vertically(rdl_vars);
	clear_lines_below_cursor(rdl_vars);
	print_prompt(rdl_vars);
	rdl_vars->curs_colm_pos = rdl_vars->prompt_len;
	if (option == restore)
		restore_cursor_pos(rdl_vars);
	// while (rdl_vars->curs_row_pos < rdl_vars->printed_lines - 1)
	// 	move_cursor_down_vertically(rdl_vars);
	// while (rdl_vars->curs_row_pos > 0)
	// {
	// 	clear_curr_line(rdl_vars);
	// 	move_cursor_up_vertically(rdl_vars);
	// }
	// rdl_vars->curs_colm_pos = rdl_vars->curr_dirc_len;
	// clear_curr_line_after_cursor(rdl_vars->curr_dirc_len);
}

// void	clear_lines_after_cursor(t_rdline *rdl_vars, int option)
// {
// 	char	*clear_after_cursor = tgetstr("ce", NULL);
	
// 	save_curr_cursor_pos(rdl_vars);
// 	while (rdl_vars->curs_row_pos < rdl_vars->printed_lines - 1)
// 	{
// 		tputs(clear_after_cursor, 1, put_char);
// 		move_cursor_start_of_next_line(rdl_vars);
// 	}
// 	if (option == restore)
// 		restore_cursor_pos(rdl_vars);
// }

void	print_after_cursor(t_rdline *rdl_vars, char *str, int option)
{
	int		i;

	i = 0;
	save_curr_cursor_pos(rdl_vars);
	clear_curr_line_after_cursor(rdl_vars);
	while (str[i])
	{
		put_char(str[i++]);
		rdl_vars->curs_colm_pos++;
		if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
		{
			put_char(' ');
			move_cursor_left(rdl_vars);
			rdl_vars->curs_colm_pos = 0;
			rdl_vars->curs_row_pos++;
			clear_curr_line_after_cursor(rdl_vars);
		}
	}
	if (option == restore)
		restore_cursor_pos(rdl_vars);
}

void	show_old_history(t_rdline *rdl_vars)
{
	t_char_vec	*history_line;
	t_vchar_vec	*history_vec;
	int	*l_i;
	int	*c_i;

	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	history_vec = &rdl_vars->history_vec;
	history_line = rdl_vars->history_vec.elements;
	if (*l_i > 0)
	{	
		(*l_i)--;
		clear_printed_lines(rdl_vars, dont_restore);
		print_after_cursor(rdl_vars, history_line[*l_i].elements, dont_restore);
		*c_i = history_line[*l_i].last_index + 1;
		update_cursor_data(rdl_vars);
	}
}

void	show_new_history(t_rdline *rdl_vars)
{
	t_char_vec	*history_line;
	t_vchar_vec	*history_vec;
	int	*l_i;
	int	*c_i;

	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	if (*l_i < history_vec->last_index)
	{
		(*l_i)++;
		clear_printed_lines(rdl_vars, dont_restore);
		print_after_cursor(rdl_vars, history_line[*l_i].elements, dont_restore);
		if (history_line[*l_i].last_index != 0)
			*c_i = history_line[*l_i].last_index + 1;
		else
			*c_i = history_line[*l_i].last_index;
		update_cursor_data(rdl_vars);
	}
}

void	move_left(t_rdline *rdl_vars)
{
	int *curs_colm_pos;
	int	*c_i;

	c_i = &rdl_vars->c_i;
	curs_colm_pos = &rdl_vars->curs_colm_pos;
	if (*c_i > 0)
	{
		(*c_i)--;
		if (*curs_colm_pos == 0)
			move_cursor_end_of_prec_line(rdl_vars);
		else
			move_cursor_left(rdl_vars);
		update_cursor_data(rdl_vars);
	}
}

void	move_right(t_rdline *rdl_vars)
{
	t_char_vec	*history_line;
	t_vchar_vec *history_vec;
	int *curs_colm_pos;
	int	*l_i;
	int	*c_i;

	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	curs_colm_pos = &rdl_vars->curs_colm_pos;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	if (*c_i < history_line[*l_i].used_size)
	{
		(*c_i)++;
		if (*curs_colm_pos == rdl_vars->width_of_screen - 1)
			move_cursor_start_of_next_line(rdl_vars);
		else
			move_cursor_right(rdl_vars);
		update_cursor_data(rdl_vars);
	}
}

void	print_curr_char(t_rdline *rdl_vars, char c)
{
	t_char_vec	*history_line;
	t_vchar_vec	*history_vec;
	int	*l_i;
	int	*c_i;

	c_i = &rdl_vars->c_i;
	l_i = &rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	history_line[*l_i].add_new_element_at_index(&history_line[*l_i], c, *c_i);
	put_char(history_line[*l_i].elements[*c_i]);
	rdl_vars->curs_colm_pos++;
	(*c_i)++;
	if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
	{
		put_char(' ');
		move_cursor_left(rdl_vars);
		rdl_vars->curs_row_pos++;
		rdl_vars->curs_colm_pos = 0;
	}
	print_after_cursor(rdl_vars, history_line[*l_i].elements + *c_i, restore);
	update_cursor_data(rdl_vars);
}

void	erase_and_remove_char(t_rdline *rdl_vars)
{
	t_vchar_vec	*history_vec;
	t_char_vec	*hstry_line;
	int *curs_colm_pos;
	int	*l_i;
	int	*c_i;

	c_i = &rdl_vars->c_i;
	l_i = &rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	hstry_line = history_vec->elements;
	curs_colm_pos = &rdl_vars->curs_colm_pos;
	if (*c_i > 0)
	{
		(*c_i)--;
		hstry_line[*l_i].delete_element_at_index(&hstry_line[*l_i], *c_i);
		if (*curs_colm_pos == 0)
			move_cursor_end_of_prec_line(rdl_vars);
		else
			move_cursor_left(rdl_vars);
		print_after_cursor(rdl_vars, hstry_line[*l_i].elements + *c_i, restore);
		update_cursor_data(rdl_vars);
	}
}

void	save_curr_line_to_history(t_rdline *rdl_vars)
{
	t_char_vec	*hstry_line;
	t_vchar_vec	*hstry_vec;
	t_char_vec	new_vec;
	int			*l_i;

	l_i = &rdl_vars->l_i;
	hstry_vec = &rdl_vars->history_vec;
	hstry_line = hstry_vec->elements;
	initialize_vec_of_char(&new_vec);
	new_vec.add_set_of_elements(&new_vec, hstry_line[*l_i].elements);
	hstry_vec->delete_last_element(hstry_vec);
	hstry_vec->add_new_element(hstry_vec, new_vec);
}

void	restore_old_history_of_curr_line(t_rdline *rdl_vars)
{
	char		**old_history;
	t_vchar_vec	*history_vec;
	t_char_vec	old_line;
	int			*l_i;

	l_i = &rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	old_history = rdl_vars->old_history;
	initialize_vec_of_char(&old_line);
	if (rdl_vars->old_history[*l_i] != NULL)
	{
		old_line.add_set_of_elements(&old_line, old_history[*l_i]);
		history_vec->delete_element_at_index(history_vec, *l_i);
		history_vec->add_new_element_at_index(history_vec, old_line, *l_i);
	}
}

void	store_curr_line(t_rdline *rdl_vars)
{
	t_char_vec	*history_line;
	t_vchar_vec	*history_vec;
	int	*l_i;

	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	l_i = &rdl_vars->l_i;
	rdl_vars->line = strdup(history_line[*l_i].elements);
	if (history_line[*l_i].used_size > 0)
	{
		save_curr_line_to_history(rdl_vars);
		restore_old_history_of_curr_line(rdl_vars);
	}
	else
		history_vec->delete_last_element(history_vec);
}

void	detect_screen_resizing(t_rdline *rdl_vars)
{
	int		new_screen_width_size;

	new_screen_width_size = get_screen_width();
	rdl_vars->width_of_screen = new_screen_width_size;
	update_cursor_data(rdl_vars);
}

void	sigwinch_handler(int signo)
{
	if (signo == SIGWINCH)
		detect_screen_resizing(&g_vars.rdl_vars);
}

void	add_empty_char_vec_to_history_vec(t_vchar_vec *history_vec)
{
	t_char_vec	char_vec;

	initialize_vec_of_char(&char_vec);
	history_vec->add_new_element(history_vec, char_vec);
}

char	**convert_history_vec_to_array(t_vchar_vec *history_vec)
{
	int		i;
	char	**array;
	t_char_vec	*line;

	i = 0;
	line = history_vec->elements;
	array = malloc(sizeof(char*) * history_vec->used_size + 1);
	while (i < history_vec->used_size)
	{
		array[i] = strdup(line[i].elements);
		i++;
	}
	array[i] = NULL;
	return (array);
}

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
		erase_and_remove_char(rdl_vars);
	else if (key == printable)
		print_curr_char(rdl_vars, c);
	else if (key == enter)
	{
		store_curr_line(rdl_vars);
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
	free_array(rdl_vars->old_history);
}

void	enable_raw_mode()
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	disable_raw_mode(struct termios old_termios_state)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios_state);
}

void	initialize_termios_struct(t_termios *original_termios_state)
{
	char		*term_type;

	term_type = getenv("TERM");
	tgetent(NULL, term_type);
	tcgetattr(STDIN_FILENO, original_termios_state);
}

void	initialize_capabilities(t_capability *capability)
{
	capability->mv_cursor_up_vertically = tgetstr("up", NULL);
	capability->mv_cursor_down_vertically = tgetstr("do", NULL);
	capability->mv_cursor_left = tgetstr("le", NULL);
	capability->mv_cursor_right = tgetstr("nd", NULL);
	capability->clear_line_after_cursor = tgetstr("ce", NULL);
	capability->clear_lines_below = tgetstr("cd", NULL);
}

void	initialize_rdl_vars(t_rdline *rdl_vars)
{
	rdl_vars->key_seq_trie = initialize_key_seq_trie();
	initialize_vec_of_char_vec(&rdl_vars->history_vec);
	initialize_capabilities(&rdl_vars->capability);
	rdl_vars->c_i = 0;
	rdl_vars->l_i = 0;
	rdl_vars->curs_row_pos = 0;
	rdl_vars->curs_colm_pos = 0;
	rdl_vars->curs_row_old_pos = 0;
	rdl_vars->curs_colm_old_pos = 0;
	rdl_vars->prompt_len = 0;
	rdl_vars->printed_lines = 0;
	rdl_vars->width_of_screen = 0;
	rdl_vars->line = NULL;
	rdl_vars->prompt = NULL;
	rdl_vars->old_history = NULL;
}


void	read_line(char **line)
{
	static t_termios	original_termios_state;
	static int			is_initialized = false;
	t_rdline			*rdl_vars;
	
	rdl_vars = &g_vars.rdl_vars;
	if (is_initialized == false)
	{
		initialize_termios_struct(&original_termios_state);
		initialize_rdl_vars(rdl_vars);
		is_initialized = true;
		// fd = fopen("./debug.txt", "w+");
	}
	enable_raw_mode();
	process_input(line, &g_vars.rdl_vars);
	disable_raw_mode(original_termios_state);
}

// void	disable_auto_wrapping()
// {
// 	// char	*terminal_device_file;
// 	// int		tty_fd;

// 	// terminal_device_file = NULL;
// 	// if (isatty(STDIN_FILENO))
// 	// 	terminal_device_file = ttyname(STDIN_FILENO);
// 	// else if (isatty(STDOUT_FILENO))
// 	// 	terminal_device_file = ttyname(STDOUT_FILENO);
// 	// else if (isatty(STDERR_FILENO))
// 	// 	terminal_device_file = ttyname(STDERR_FILENO);
// 	// if (terminal_device_file != NULL)
// 	// {
// 	// 	tty_fd = open(terminal_device_file, O_WRONLY);
// 	// 	// write(tty_fd, "\e[?7l\n", strlen("\e[?7l\n"));
// 	// 	printf("\033[?7l");
// 	// }
// 	// printf("%d\n",tgetflag("am"));
// }

// void	read_from_stdin(t_rdline *vars)
// {
// 	int		key;
// 	char	c;

// 	signal(SIGWINCH, sigwinch_handler);
// 	key = none;
// 	while (read(STDIN_FILENO, &c, 1))
// 	{
// 		key = get_key(vars->key_seq_trie, c);
// 		if (key == waiting)
// 			continue ;
// 		start_key_action(vars, key, c);
// 		if (key == enter)
// 			break ;
// 	}
// }