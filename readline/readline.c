#include <ctype.h>
#include <termcap.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./readline.h"

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
	ft_putstr(tgoto(ch_cap, 0, col));
}

void	clear_after_cursor(int cursor_pos)
{
	move_cursor_to_colum(cursor_pos);
	char	*clear_line = tgetstr("ce", NULL);
	ft_putstr(clear_line);
}

void	show_old_history(t_readline *rdl_vars)
{
	t_char_vec	*history_line;
	int	curr_dirc_len;
	int *cursor_pos;
	int	*l_i;
	int	*c_i;

	history_line = rdl_vars->history_vec.elements;
	curr_dirc_len = rdl_vars->curr_dirc_len;
	cursor_pos = &rdl_vars->cursor_pos;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	if (*l_i > 0)
	{	
		(*l_i)--;
		clear_after_cursor(curr_dirc_len);
		ft_putstr(history_line[*l_i].elements);
		*c_i = history_line[*l_i].last_index + 1;
		*cursor_pos = curr_dirc_len + *c_i;
	}
}

void	show_new_history(t_readline *rdl_vars, t_vchar_vec *history_vec)
{
	t_char_vec	*history_line;
	int	curr_dirc_len;
	int *cursor_pos;
	int	*l_i;
	int	*c_i;

	curr_dirc_len = rdl_vars->curr_dirc_len;
	cursor_pos = &rdl_vars->cursor_pos;
	history_line = history_vec->elements;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	if (*l_i < history_vec->used_size - 1)
	{
		(*l_i)++;
		clear_after_cursor(curr_dirc_len);
		ft_putstr(history_line[*l_i].elements);
		if (history_line[*l_i].last_index != 0)
			*c_i = history_line[*l_i].last_index + 1;
		else
			*c_i = history_line[*l_i].last_index;
		*cursor_pos = curr_dirc_len + *c_i;
	}
}

void	move_cursor_left(t_readline *rdl_vars)
{
	int *cursor_pos;
	int	*c_i;

	cursor_pos = &rdl_vars->cursor_pos;
	c_i = &rdl_vars->c_i;
	if (*c_i > 0)
	{
		char	*le_cap = tgetstr("le", NULL);
		ft_putstr(le_cap);
		(*c_i)--;
		(*cursor_pos)--;
	}
}

void	move_cursor_right(t_readline *rdl_vars, t_vchar_vec *history_vec)
{
	t_char_vec	*history_line;
	int *cursor_pos;
	int	*l_i;
	int	*c_i;

	cursor_pos = &rdl_vars->cursor_pos;
	history_line = history_vec->elements;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	if (*c_i <= history_line[*l_i].last_index && history_line[*l_i].last_index != 0)
	{
		char	*nd_cap = tgetstr("nd", NULL);
		ft_putstr(nd_cap);
		(*c_i)++;
		(*cursor_pos)++;
	}
}

void	print_curr_char(char c, t_readline *rdl_vars, t_vchar_vec *hstry_vec)
{
	t_char_vec	*history_line;
	int *cursor_pos;
	int	*l_i;
	int	*c_i;

	cursor_pos = &rdl_vars->cursor_pos;
	history_line = hstry_vec->elements;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	history_line[*l_i].add_new_element_at_index(&history_line[*l_i], c, *c_i);
	clear_after_cursor(*cursor_pos);
	ft_putstr(history_line[*l_i].elements + *c_i);
	(*c_i)++;
	(*cursor_pos)++;
	move_cursor_to_colum(*cursor_pos);
}

void	erase_and_remove_char(t_readline *rdl_vars, t_vchar_vec *history_vec)
{
	t_char_vec	*history_line;
	int *cursor_pos;
	int	*l_i;
	int	*c_i;

	history_line = history_vec->elements;
	cursor_pos = &rdl_vars->cursor_pos;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	if (*c_i > 0)
	{
		(*c_i)--;
		(*cursor_pos)--;
		history_line[*l_i].delete_element_at_index(&history_line[*l_i], *c_i);
		clear_after_cursor(*cursor_pos);
		ft_putstr(history_line[*l_i].elements + *c_i);
		move_cursor_to_colum(*cursor_pos);
	}
}
void	save_curr_line_to_history(t_readline *rdl_vars)
{
	int			*l_i;
	t_vchar_vec	*history_vec;
	t_char_vec	*history_line;
	t_char_vec	new_vec;

	l_i = &rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	initialize_vec_of_char(&new_vec);
	new_vec.add_set_of_elements_at_index(&new_vec, history_line[*l_i].elements, 0);
	history_vec->delete_element_at_index(history_vec, history_vec->used_size - 1);
	history_vec->add_new_element(history_vec, new_vec);

}

void	restore_old_history_of_curr_line(t_readline *rdl_vars)
{
	int			*l_i;
	char		**old_history;
	t_vchar_vec	*history_vec;
	t_char_vec	old_line;

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

void	store_curr_line(t_readline *rdl_vars, t_vchar_vec *history_vec)
{
	t_char_vec	*history_line;
	int cursor_pos;
	int	*l_i;
	int	*c_i;

	history_line = history_vec->elements;
	cursor_pos = rdl_vars->cursor_pos;
	l_i = &rdl_vars->l_i;
	c_i = &rdl_vars->c_i;
	rdl_vars->line = strdup(history_line[*l_i].elements);
	if (history_line[*l_i].used_size > 0)
	{
		save_curr_line_to_history(rdl_vars);
		restore_old_history_of_curr_line(rdl_vars);
	}
	else
		history_vec->delete_element_at_index(history_vec, history_vec->used_size - 1);
}

void	start_key_action(t_readline *rdl_vars, int key, char c)
{
	t_vchar_vec		*history_vec;

	history_vec = &rdl_vars->history_vec;
	if (key == up_arrow)
		show_old_history(rdl_vars);
	else if (key == down_arrow)
		show_new_history(rdl_vars, history_vec);
	else if (key == left_arrow)
		move_cursor_left(rdl_vars);
	else if (key == right_arrow)
		move_cursor_right(rdl_vars, history_vec);
	else if (key == backspace)
		erase_and_remove_char(rdl_vars, history_vec);
	else if (key == printable)
		print_curr_char(c, rdl_vars, history_vec);
	else if (key == enter)
	{
		store_curr_line(rdl_vars, &rdl_vars->history_vec);
		ft_putstr("\n");
	}
}

void	read_from_stdin(t_readline *readline_vars)
{
	int		key;
	char	c;

	key = none;
	while (read(STDIN_FILENO, &c, 1))
	{
		key = get_key(readline_vars->key_seq_trie, c);
		if (key == waiting)
			continue ;
		start_key_action(readline_vars, key, c);
		if (key == enter)
			break ;
	}
}

void	process_input(char **line, t_readline *readline_vars)
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
	readline_vars->cursor_pos = readline_vars->curr_dirc_len;
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


void	readline(char **line)
{
	static int			is_initialized = false;
	static t_termios	original_termios_state;

	if (is_initialized == false)
	{
		initialize_termios_struct(&original_termios_state);
		initialize_vec_of_char_vec(&readline_vars.history_vec);
		readline_vars.key_seq_trie = initialize_key_seq_trie();
		readline_vars.l_i = 0;
		readline_vars.c_i = 0;
		readline_vars.cursor_pos = 0;
		readline_vars.curr_dirc_len = 0;
		readline_vars.line = NULL;
		is_initialized = true;
	}
	enable_raw_mode();
	process_input(line, &readline_vars);
	disable_raw_mode(original_termios_state);
}
