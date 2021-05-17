#include <ctype.h>
#include <termcap.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./readline.h"

#include <fcntl.h>
FILE		*fd;

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int		ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}

int		ft_putchar(int c)
{
	int		len;

	len = write(1, &c, 1);
	return (len);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++,1);
}

int		print_current_dir()
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
	len = i - keep_index;
	write(1, GRN, strlen(GRN));
	write(1, "➜  ", 5);
	write(1, curr_dir + keep_index, len);
	write(1, " ", 1);
	free(curr_dir);
	write(1, WHT, strlen(WHT));
	return (len + 4);
}


// void	move_cursor_up_vetically(t_capability capability)
// {
// 	tputs(capability.mv_cursor_up_vertically, 1, ft_putchar);
// }
void	move_cursor_to_colum(t_rdline *rdl_vars, int col)
{
	char	*ch_cap = tgetstr("ch", NULL);
	tputs(tgoto(ch_cap, 0, col), 1, ft_putchar);
	rdl_vars->curs_colm_pos = col;
}


void	move_cursor_up_vertically(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_up_vertically, 1, ft_putchar);
	rdl_vars->curs_row_pos--;
}

void	move_cursor_down_vertically(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_down_vertically, 1, ft_putchar);
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
	rdl_vars->curs_colm_pos = rdl_vars->width_of_screen - 1;
}

void	move_cursor_right(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_right, 1, ft_putchar);
	rdl_vars->curs_colm_pos++;
}

void	move_cursor_left(t_rdline *rdl_vars)
{
	tputs(rdl_vars->capability.mv_cursor_left, 1, ft_putchar);
	rdl_vars->curs_colm_pos--;
}

int		get_screen_width(t_rdline *rdl_vars)
{
	struct winsize w;
	
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}


void	clear_curr_line_after_cursor(t_rdline *rdl_vars)
{
	move_cursor_to_colum(rdl_vars, rdl_vars->curs_colm_pos);
	char	*clear_after_cursor = tgetstr("ce", NULL);
	tputs(clear_after_cursor, 1, ft_putchar);
}

void	clear_curr_line(t_rdline *rdl_vars)
{
	rdl_vars->curs_colm_pos = 0;
	move_cursor_to_colum(rdl_vars, rdl_vars->curs_colm_pos);
	char	*clear_after_cursor = tgetstr("ce", NULL);
	tputs(clear_after_cursor, 1, ft_putchar);
}

void	clear_lines_below_cursor(t_rdline *rdl_vars)
{
	move_cursor_to_colum(rdl_vars, 0);
	tputs(rdl_vars->capability.clear_lines_below, 1, ft_putchar);
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

void	update_cursor_data(t_rdline *vars)
{
	vars->curs_colm_pos = (vars->curr_dirc_len + vars->c_i) % vars->width_of_screen;
	vars->curs_row_pos = (vars->curr_dirc_len + vars->c_i) / vars->width_of_screen;
	vars->printed_lines = (vars->curr_dirc_len + vars->history_vec.elements[vars->l_i].last_index) / vars->width_of_screen + 1;
}

void	restore_cursor_pos(t_rdline *rdl_vars)
{
	while (rdl_vars->curs_row_pos > rdl_vars->curs_row_old_pos)
		move_cursor_up_vertically(rdl_vars);
	move_cursor_to_colum(rdl_vars, rdl_vars->curs_colm_old_pos);
}

void	save_curr_cursor_pos(t_rdline *rdl_vars)
{
	rdl_vars->curs_colm_old_pos = rdl_vars->curs_colm_pos;
	rdl_vars->curs_row_old_pos = rdl_vars->curs_row_pos;
}

void	clear_printed_lines(t_rdline *rdl_vars)
{
	while (rdl_vars->curs_row_pos > 0)
		move_cursor_up_vertically(rdl_vars);
	clear_lines_below_cursor(rdl_vars);
	rdl_vars->curs_colm_pos = print_current_dir();
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

void	clear_lines_after_cursor(t_rdline *vars)
{
	char	*clear_after_cursor = tgetstr("ce", NULL);
	
	save_curr_cursor_pos(vars);
	while (vars->curs_row_pos < vars->printed_lines - 1)
	{
		tputs(clear_after_cursor, 1, ft_putchar);
		move_cursor_start_of_next_line(vars);
		vars->curs_row_pos++;
	}
	restore_cursor_pos(vars);
}

void	print_after_cursor(t_rdline *rdl_vars, char *str, int option)
{
	int		i;

	i = 0;
	save_curr_cursor_pos(rdl_vars);
	clear_curr_line_after_cursor(rdl_vars);
	while (str[i])
	{
		ft_putchar(str[i++]);
		rdl_vars->curs_colm_pos++;
		if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
		{
			ft_putchar(' ');
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
		clear_printed_lines(rdl_vars);
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
		clear_printed_lines(rdl_vars);
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

	curs_colm_pos = &rdl_vars->curs_colm_pos;
	c_i = &rdl_vars->c_i;
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
	curs_colm_pos = &rdl_vars->curs_colm_pos;
	history_line = history_vec->elements;
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
	t_char_vec	*hstry_line;
	t_vchar_vec	*hstry_vec;
	int *curs_colm_pos;
	int	*l_i;
	int	*c_i;

	hstry_vec = &rdl_vars->history_vec;
	hstry_line = hstry_vec->elements;
	curs_colm_pos = &rdl_vars->curs_colm_pos;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	hstry_line[*l_i].add_new_element_at_index(&hstry_line[*l_i], c, *c_i);
	ft_putchar(hstry_line[*l_i].elements[*c_i]);
	rdl_vars->curs_colm_pos++;
	(*c_i)++;
	if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
	{
		ft_putchar(' ');
		move_cursor_left(rdl_vars);
		rdl_vars->curs_row_pos++;
		rdl_vars->curs_colm_pos = 0;
	}
	print_after_cursor(rdl_vars, hstry_line[*l_i].elements + *c_i, restore);
	update_cursor_data(rdl_vars);
}

void	erase_and_remove_char(t_rdline *rdl_vars)
{
	t_vchar_vec	*history_vec;
	t_char_vec	*hstry_line;
	int *curs_colm_pos;
	int	*l_i;
	int	*c_i;

	history_vec = &rdl_vars->history_vec;
	hstry_line = history_vec->elements;
	curs_colm_pos = &rdl_vars->curs_colm_pos;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
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
	hstry_vec->delete_element_at_index(hstry_vec, hstry_vec->used_size - 1);
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
		old_line.add_set_of_elements_at_index(&old_line, old_history[*l_i], 0);
		history_vec->delete_element_at_index(history_vec, *l_i);
		history_vec->add_new_element_at_index(history_vec, old_line, *l_i);
	}
}

void	store_curr_line(t_rdline *rdl_vars)
{
	t_char_vec	*history_line;
	t_vchar_vec	*hstry_vec;
	int curs_colm_pos;
	int	*l_i;
	int	*c_i;

	hstry_vec = &rdl_vars->history_vec;
	history_line = hstry_vec->elements;
	curs_colm_pos = rdl_vars->curs_colm_pos;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	rdl_vars->line = strdup(history_line[*l_i].elements);
	if (history_line[*l_i].used_size > 0)
	{
		save_curr_line_to_history(rdl_vars);
		restore_old_history_of_curr_line(rdl_vars);
	}
	else
		hstry_vec->delete_element_at_index(hstry_vec, hstry_vec->last_index);
}

void	detect_screen_resizing(t_rdline *rdl_vars)
{
	int		new_screen_width_size;

	new_screen_width_size = get_screen_width(rdl_vars);
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
	rdl_vars->curr_dirc_len = print_current_dir();
	rdl_vars->width_of_screen = get_screen_width(rdl_vars);
	rdl_vars->c_i = 0;
	rdl_vars->l_i = history_vec->used_size - 1;
	rdl_vars->curs_row_pos = 0;
	rdl_vars->curs_colm_pos = rdl_vars->curr_dirc_len;
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
		ft_putstr("\n");
	}
}

void	process_input(char **line, t_rdline *rdl_vars)
{
	int		key;
	char	c;

	key = none;
	set_rdl_vars(rdl_vars);
	signal(SIGWINCH, sigwinch_handler);
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
	rdl_vars->curr_dirc_len = 0;
	rdl_vars->printed_lines = 0;
	rdl_vars->width_of_screen = 0;
	rdl_vars->line = NULL;
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
		fd = fopen("./debug.txt", "w+");
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