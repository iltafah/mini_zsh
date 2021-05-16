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

void	move_cursor_to_colum(int col)
{
	char	*ch_cap = tgetstr("ch", NULL);
	tputs(tgoto(ch_cap, 0, col), 1, ft_putchar);
}

void	move_cursor_up_vetically(t_capability capability)
{
	tputs(capability.mv_cursor_up_vertically, 1, ft_putchar);
}

void	move_cursor_start_of_next_line(t_capability capability)
{
	move_cursor_to_colum(0);
	tputs(capability.mv_cursor_down_vertically, 1, ft_putchar);
}

void	move_cursor_end_of_prec_line(t_gvars *vars)
{
	tputs(vars->capability.mv_cursor_up_vertically, 1, ft_putchar);
	move_cursor_to_colum(vars->width_of_screen - 1);
	vars->curs_colm_pos = vars->width_of_screen - 1;
}

void	move_cursor_up_vertically(t_gvars *vars)
{
	tputs(vars->capability.mv_cursor_up_vertically, 1, ft_putchar);
	vars->curs_row_pos--;
}

void	move_cursor_down_vertically(t_gvars *vars)
{
	tputs(vars->capability.mv_cursor_down_vertically, 1, ft_putchar);
	vars->curs_row_pos++;
}

void	move_cursor_right(t_gvars *vars)
{
	tputs(vars->capability.mv_cursor_right, 1, ft_putchar);
	vars->curs_colm_pos++;
}

void	move_cursor_left(t_gvars *vars)
{
	tputs(vars->capability.mv_cursor_left, 1, ft_putchar);
	vars->curs_colm_pos--;
}

int		get_screen_width(t_gvars *vars)
{
	struct winsize w;
	
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}


void	clear_curr_line_after_cursor(int curs_colm_pos)
{
	move_cursor_to_colum(curs_colm_pos);
	char	*clear_after_cursor = tgetstr("ce", NULL);
	tputs(clear_after_cursor, 1, ft_putchar);
}

void	clear_curr_line(t_gvars *vars)
{
	vars->curs_colm_pos = 0;
	move_cursor_to_colum(vars->curs_colm_pos);
	char	*clear_after_cursor = tgetstr("ce", NULL);
	tputs(clear_after_cursor, 1, ft_putchar);
}

void	clear_lines_below_cursor(t_capability capability)
{
	move_cursor_to_colum(0);
	tputs(capability.clear_lines_below, 1, ft_putchar);
}

// void	clear_lines_after_and_below_cursor(t_gvars *vars)
// {
// 	clear_curr_line_after_cursor(vars->curs_colm_pos);
// 	if (vars->curs_row_pos < vars->printed_lines)
// 	{
// 		move_cursor_start_of_next_line(vars->capability);
// 		clear_lines_below_cursor(vars->capability);
// 	}
// }

void	update_cursor_data(t_gvars *vars)
{
	vars->curs_colm_pos = (vars->curr_dirc_len + vars->c_i) % vars->width_of_screen;
	vars->curs_row_pos = (vars->curr_dirc_len + vars->c_i) / vars->width_of_screen;
	vars->printed_lines = (vars->curr_dirc_len + vars->history_vec.elements[vars->l_i].last_index) / vars->width_of_screen + 1;
}

void	restore_cursor_pos(t_gvars *g_vars)
{
	while (g_vars->curs_row_pos > g_vars->curs_row_old_pos)
	{
		move_cursor_up_vetically(g_vars->capability);
		g_vars->curs_row_pos--;
	}
	move_cursor_to_colum(g_vars->curs_colm_old_pos);
	g_vars->curs_colm_pos = g_vars->curs_colm_old_pos;
}

void	save_curr_cursor_pos(t_gvars *g_vars)
{
	// update_cursor_data(g_vars);
	g_vars->curs_colm_old_pos = g_vars->curs_colm_pos;
	g_vars->curs_row_old_pos = g_vars->curs_row_pos;
}

void	clear_printed_lines(t_gvars *g_vars)
{
	while (g_vars->curs_row_pos > 0)
	{
		move_cursor_up_vetically(g_vars->capability);
		g_vars->curs_row_pos--;
	}
	clear_lines_below_cursor(g_vars->capability);
	g_vars->curs_colm_pos = print_current_dir();
	fprintf(fd, "curs_colm dirc = %d\n", g_vars->curs_colm_pos);
	fflush(fd);
	// while (g_vars->curs_row_pos < g_vars->printed_lines - 1)
	// 	move_cursor_down_vertically(g_vars);
	// while (g_vars->curs_row_pos > 0)
	// {
	// 	clear_curr_line(g_vars);
	// 	move_cursor_up_vertically(g_vars);
	// }
	// g_vars->curs_colm_pos = g_vars->curr_dirc_len;
	// clear_curr_line_after_cursor(g_vars->curr_dirc_len);
}

void	clear_lines_after_cursor(t_gvars *vars)
{
	char	*clear_after_cursor = tgetstr("ce", NULL);
	
	save_curr_cursor_pos(vars);
	while (vars->curs_row_pos < vars->printed_lines - 1)
	{
		tputs(clear_after_cursor, 1, ft_putchar);
		move_cursor_start_of_next_line(vars->capability);
		vars->curs_row_pos++;
	}
	restore_cursor_pos(vars);
}

void	print_after_cursor(t_gvars *vars, char *str, int option)
{
	int		i;

		// fprintf(fd, "%d ?= %d\n", vars->curs_colm_pos, vars->curr_dirc_len);
		// fflush(fd);
	i = 0;
	save_curr_cursor_pos(vars);
	clear_curr_line_after_cursor(vars->curs_colm_pos);
	while (str[i])
	{
		ft_putchar(str[i++]);
		vars->curs_colm_pos++;
		if (vars->curs_colm_pos == vars->width_of_screen)
		{
			ft_putchar(' ');
			move_cursor_left(vars);
			vars->curs_colm_pos = 0;
			vars->curs_row_pos++;
			clear_curr_line_after_cursor(vars->curs_colm_pos);
		}
		// if (vars->curs_colm_pos == vars->width_of_screen)
		// {
			// move_cursor_start_of_next_line(vars->capability);
			// vars->curs_colm_pos = 0;
			// vars->curs_row_pos += 1;
		    // clear_curr_line_after_cursor(vars->curs_colm_pos);
		// }
	}
	if (option == restore)
		restore_cursor_pos(vars);
}

void	show_old_history(t_gvars *g_vars)
{
	t_char_vec	*history_line;
	int	curr_dirc_len;
	int *curs_colm_pos;
	int	*l_i;
	int	*c_i;

	history_line = g_vars->history_vec.elements;
	curr_dirc_len = g_vars->curr_dirc_len;
	curs_colm_pos = &g_vars->curs_colm_pos;
	l_i = &g_vars->l_i;
	c_i = &g_vars->c_i;
	if (*l_i > 0)
	{	
		(*l_i)--;
		clear_printed_lines(g_vars);
		print_after_cursor(g_vars, history_line[*l_i].elements, dont_restore);
		*c_i = history_line[*l_i].last_index + 1;
		update_cursor_data(g_vars);
	}
		// fprintf(fd, ">>%d ?= %d<<\n", g_vars->curs_colm_pos, g_vars->curr_dirc_len);
		// sleep (2);
}

void	show_new_history(t_gvars *g_vars, t_vchar_vec *history_vec)
{
	t_char_vec	*history_line;
	int	curr_dirc_len;
	int *curs_colm_pos;
	int	*l_i;
	int	*c_i;

	curr_dirc_len = g_vars->curr_dirc_len;
	curs_colm_pos = &g_vars->curs_colm_pos;
	history_line = history_vec->elements;
	l_i = &g_vars->l_i;
	c_i = &g_vars->c_i;
	if (*l_i < history_vec->used_size - 1)
	{
		(*l_i)++;
		clear_printed_lines(g_vars);
		print_after_cursor(g_vars, history_line[*l_i].elements, dont_restore);
		if (history_line[*l_i].last_index != 0)
			*c_i = history_line[*l_i].last_index + 1;
		else
			*c_i = history_line[*l_i].last_index;
		update_cursor_data(g_vars);
	}
}

void	move_left(t_gvars *g_vars)
{
	int *curs_colm_pos;
	int	*c_i;

	curs_colm_pos = &g_vars->curs_colm_pos;
	c_i = &g_vars->c_i;
	if (*c_i > 0)
	{
		(*c_i)--;
		if (*curs_colm_pos == 0)
		{
			move_cursor_end_of_prec_line(g_vars);
			// (*curs_colm_pos) = g_vars->width_of_screen - 1;
			// g_vars->curs_row_pos--;
		}
		else
		{
			move_cursor_left(g_vars);
			// (*curs_colm_pos)--;
		}
		update_cursor_data(g_vars);
	}
}

void	move_right(t_gvars *g_vars, t_vchar_vec *history_vec)
{
	t_char_vec	*history_line;
	int *curs_colm_pos;
	int	*l_i;
	int	*c_i;

	curs_colm_pos = &g_vars->curs_colm_pos;
	history_line = history_vec->elements;
	l_i = &g_vars->l_i;
	c_i = &g_vars->c_i;
	if (*c_i < history_line[*l_i].used_size)
	{
		(*c_i)++;
		if (*curs_colm_pos == g_vars->width_of_screen - 1)
		{
			move_cursor_start_of_next_line(g_vars->capability);
			// (*curs_colm_pos) = 0;
			// g_vars->curs_row_pos++;
		}
		else
		{
			// char	*nd_cap = tgetstr("nd", NULL);
			// ft_putstr(nd_cap);
			move_cursor_right(g_vars);
			// (*curs_colm_pos)++;
		}
		// fprintf(fd, "cursor pos : [%d]\n", *curs_colm_pos);
		// fflush(fd);
		update_cursor_data(g_vars);
	}
}


void	print_curr_char(char c, t_gvars *g_vars, t_vchar_vec *hstry_vec)
{

	t_char_vec	*history_line;
	int *curs_colm_pos;
	int	*l_i;
	int	*c_i;

	curs_colm_pos = &g_vars->curs_colm_pos;
	history_line = hstry_vec->elements;
	l_i = &g_vars->l_i;
	c_i = &g_vars->c_i;
	history_line[*l_i].add_new_element_at_index(&history_line[*l_i], c, *c_i);
	

	ft_putchar(history_line[*l_i].elements[*c_i]);
	g_vars->curs_colm_pos++;
	if (g_vars->curs_colm_pos == g_vars->width_of_screen)
	{
		ft_putchar(' ');
		move_cursor_left(g_vars);
		g_vars->curs_row_pos++;
		g_vars->curs_colm_pos = 0;
	}
	(*c_i)++;
	update_cursor_data(g_vars);
	// tputs(tgetstr("im", NULL), 1, ft_putchar);
	// tputs(tgetstr("ic", NULL), 1, ft_putchar);
	// ft_putchar(history_line[*l_i].elements[*c_i]);
	// tputs(tgetstr("ip", NULL), 1, ft_putchar);
	// tputs(tgetstr("ei", NULL), 1, ft_putchar);
}

void	erase_and_remove_char(t_gvars *g_vars, t_vchar_vec *history_vec)
{
	t_char_vec	*history_line;
	int *curs_colm_pos;
	int	*l_i;
	int	*c_i;

	history_line = history_vec->elements;
	curs_colm_pos = &g_vars->curs_colm_pos;
	l_i = &g_vars->l_i;
	c_i = &g_vars->c_i;
	if (*c_i > 0)
	{
		(*c_i)--;
		history_line[*l_i].delete_element_at_index(&history_line[*l_i], *c_i);
		if (*curs_colm_pos == 0)
			move_cursor_end_of_prec_line(g_vars);
		else
			move_cursor_left(g_vars);
		print_after_cursor(g_vars, history_line[*l_i].elements + *c_i, restore);
		update_cursor_data(g_vars);
	}
}

void	save_curr_line_to_history(t_gvars *g_vars)
{
	int			*l_i;
	t_vchar_vec	*hstry_vec;
	t_char_vec	*hstry_line;
	t_char_vec	new_vec;

	l_i = &g_vars->l_i;
	hstry_vec = &g_vars->history_vec;
	hstry_line = hstry_vec->elements;
	initialize_vec_of_char(&new_vec);
	new_vec.add_set_of_elements(&new_vec, hstry_line[*l_i].elements);
	hstry_vec->delete_element_at_index(hstry_vec, hstry_vec->used_size - 1);
	hstry_vec->add_new_element(hstry_vec, new_vec);
}

void	restore_old_history_of_curr_line(t_gvars *g_vars)
{
	int			*l_i;
	char		**old_history;
	t_vchar_vec	*history_vec;
	t_char_vec	old_line;

	l_i = &g_vars->l_i;
	history_vec = &g_vars->history_vec;
	old_history = g_vars->old_history;
	initialize_vec_of_char(&old_line);
	if (g_vars->old_history[*l_i] != NULL)
	{
		old_line.add_set_of_elements_at_index(&old_line, old_history[*l_i], 0);
		history_vec->delete_element_at_index(history_vec, *l_i);
		history_vec->add_new_element_at_index(history_vec, old_line, *l_i);
	}
}

void	store_curr_line(t_gvars *g_vars, t_vchar_vec *hstry_vec)
{
	t_char_vec	*history_line;
	int curs_colm_pos;
	int	*l_i;
	int	*c_i;

	history_line = hstry_vec->elements;
	curs_colm_pos = g_vars->curs_colm_pos;
	l_i = &g_vars->l_i;
	c_i = &g_vars->c_i;
	g_vars->line = strdup(history_line[*l_i].elements);
	if (history_line[*l_i].used_size > 0)
	{
		save_curr_line_to_history(g_vars);
		restore_old_history_of_curr_line(g_vars);
	}
	else
		hstry_vec->delete_element_at_index(hstry_vec, hstry_vec->last_index);
}

void	start_key_action(t_gvars *g_vars, int key, char c)
{
	t_vchar_vec		*history_vec;

	history_vec = &g_vars->history_vec;
	if (key == up_arrow)
		show_old_history(g_vars);
	else if (key == down_arrow)
		show_new_history(g_vars, history_vec);
	else if (key == left_arrow)
		move_left(g_vars);
	else if (key == right_arrow)
		move_right(g_vars, history_vec);
	else if (key == backspace)
		erase_and_remove_char(g_vars, history_vec);
	else if (key == printable)
		print_curr_char(c, g_vars, history_vec);
	else if (key == enter)
	{
		store_curr_line(g_vars, &g_vars->history_vec);
		ft_putstr("\n");
	}
}

void	detect_screen_resizing(t_gvars *vars)
{
	int		new_screen_width_size;

	new_screen_width_size = get_screen_width(vars);
	vars->width_of_screen = new_screen_width_size;


	update_cursor_data(vars);
	fprintf(fd, "new width [%d]\n", new_screen_width_size);
	fprintf(fd, "curs colm pos [%d]\n", vars->curs_colm_pos);
	fprintf(fd, "curs row pos [%d]\n", vars->curs_row_pos);
	fflush(fd);
}

void	sigwinch_handler(int signo)
{
	if (signo == SIGWINCH)
		detect_screen_resizing(&g_vars);
}

void	read_from_stdin(t_gvars *vars)
{
	int		key;
	char	c;

	signal(SIGWINCH, sigwinch_handler);

	key = none;
	while (read(STDIN_FILENO, &c, 1))
	{
		key = get_key(vars->key_seq_trie, c);
		if (key == waiting)
			continue ;
		start_key_action(vars, key, c);
		if (key == enter)
			break ;
	}
}

void	process_input(char **line, t_gvars *readline_vars)
{
	t_vchar_vec		*history_vec;
	t_char_vec		*history_line;
	history_vec = &readline_vars->history_vec;
    readline_vars->old_history = convert_history_vec_to_array(history_vec);
	add_empty_char_vec_to_history_vec(history_vec);
	history_line = history_vec->elements;
	readline_vars->c_i = 0;
	readline_vars->l_i = history_vec->used_size - 1;
	readline_vars->curr_dirc_len = print_current_dir();
	readline_vars->curs_colm_pos = readline_vars->curr_dirc_len;
	readline_vars->curs_row_pos = 0;
	readline_vars->curs_colm_old_pos = 0;
	readline_vars->curs_row_old_pos = 0;
	read_from_stdin(readline_vars);
	*line = readline_vars->line;
	free_array(readline_vars->old_history);
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


void	disable_auto_wrapping()
{
	// char	*terminal_device_file;
	// int		tty_fd;

	// terminal_device_file = NULL;
	// if (isatty(STDIN_FILENO))
	// 	terminal_device_file = ttyname(STDIN_FILENO);
	// else if (isatty(STDOUT_FILENO))
	// 	terminal_device_file = ttyname(STDOUT_FILENO);
	// else if (isatty(STDERR_FILENO))
	// 	terminal_device_file = ttyname(STDERR_FILENO);
	// if (terminal_device_file != NULL)
	// {
	// 	tty_fd = open(terminal_device_file, O_WRONLY);
	// 	// write(tty_fd, "\e[?7l\n", strlen("\e[?7l\n"));
	// 	printf("\033[?7l");
	// }
	// printf("%d\n",tgetflag("am"));
}

void	readline(char **line)
{
	static int			is_initialized = false;
	static t_termios	original_termios_state;
	
	
	if (is_initialized == false)
	{
		initialize_termios_struct(&original_termios_state);
		initialize_vec_of_char_vec(&g_vars.history_vec);
		initialize_capabilities(&g_vars.capability);
		g_vars.key_seq_trie = initialize_key_seq_trie();
		g_vars.l_i = 0;
		g_vars.c_i = 0;
		g_vars.curs_colm_pos = 0;
		g_vars.curs_colm_old_pos = 0;
		g_vars.curs_row_pos = 0;
		g_vars.curs_row_old_pos = 0;
		g_vars.curr_dirc_len = 0;
		g_vars.printed_lines = 0;
		g_vars.width_of_screen = get_screen_width(&g_vars);
		g_vars.line = NULL;
		is_initialized = true;
		fd = fopen("./debug.txt", "w+");
	}
	// ft_putstr(tgetstr("RA", NULL));
	enable_raw_mode();
	// disable_auto_wrapping();
	process_input(line, &g_vars);
	disable_raw_mode(original_termios_state);
}
