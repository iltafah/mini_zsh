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

void	enable_raw_mode()
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	disable_raw_mode(struct termios *old_termios_state)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, old_termios_state);
}

void	initialize_keys_seq(char **seq_addr)
{
	char *seq;

	seq = malloc(sizeof(char) * 4);
	seq[0] = 27;
	seq[1] = '[';
	seq[2] = '\0';
	seq[3] = '\0';
	seq[4] = '\0';
	*seq_addr = seq;
}

void	assign_keys(t_keys *keys)
{
	char	*seq;

	initialize_keys_seq(&seq);
	keys->up_arrow = strdup(seq);
	keys->up_arrow[2] = 65;
	keys->down_arrow = strdup(seq);
	keys->down_arrow[2] = 66;
	keys->right_arrow = strdup(seq);
	keys->right_arrow[2] = 67;
	keys->left_arrow = strdup(seq);
	keys->left_arrow[2] = 68;

	keys->enter = 10;
	keys->backspace = 127;
	free(seq);
}

void	add_empty_char_vec_to_history_vec()
{
	t_char_vec	char_vec;

	initialize_vec_of_char(&char_vec);
	readline_vars.history.add_new_element(&readline_vars.history, char_vec);
}

char	**convert_history_vec_to_array()
{
	int		i;
	char	**array;
	t_char_vec	*line;

	i = 0;
	line = readline_vars.history.elements;
	array = malloc(sizeof(char*) * readline_vars.history.used_size + 1);
	while (i < readline_vars.history.used_size)
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

void     edit_line(char **line)
{
	char			*buff;
	char			**old_history;
	int				l_i;
	int				c_i;
	int				cursor_pos;
	int				curr_dir_len;
	t_char_vec		*history_line;

	old_history = convert_history_vec_to_array();
	add_empty_char_vec_to_history_vec();
	history_line = readline_vars.history.elements;
	l_i = readline_vars.history.used_size - 1;
	c_i = 0;

	curr_dir_len = print_current_dir();
	cursor_pos = curr_dir_len;

	buff = malloc(sizeof(char) * 4);
	while (read(STDIN_FILENO, buff, 4))
	{
		buff[4] = '\0';
		if (ft_isprint(buff[0]))
		{
			history_line[l_i].add_new_element_at_index(&history_line[l_i], buff[0], c_i);
			clear_after_cursor(cursor_pos);
			ft_putstr(history_line[l_i].elements + c_i);
			c_i++;
			cursor_pos++;
			move_cursor_to_colum(cursor_pos);
		}
		else if (buff[0] == 27)
		{
			if (strcmp(buff, readline_vars.keys.up_arrow) == 0)
			{
				if (l_i > 0)
				{	
					l_i--;
					clear_after_cursor(curr_dir_len);
					ft_putstr(history_line[l_i].elements);
					c_i = history_line[l_i].last_index + 1;
					cursor_pos = curr_dir_len + c_i;
				}
			}
			else if (strcmp(buff, readline_vars.keys.down_arrow) == 0)
			{
				if (l_i < readline_vars.history.used_size - 1)
				{
					l_i++;
					clear_after_cursor(curr_dir_len);
					ft_putstr(history_line[l_i].elements);
					if (history_line[l_i].last_index != 0)
						c_i = history_line[l_i].last_index + 1;
					else
						c_i = history_line[l_i].last_index;
					cursor_pos = curr_dir_len + c_i;
				}
			}
			else if (strcmp(buff, readline_vars.keys.left_arrow) == 0)
			{
				if (c_i > 0)
				{
					char	*le_cap = tgetstr("le", NULL);
					ft_putstr(le_cap);
					c_i--;
					cursor_pos--;
				}
			}
			else if (strcmp(buff, readline_vars.keys.right_arrow) == 0)
			{
				if (c_i <= history_line[l_i].last_index && history_line[l_i].last_index != 0)
				{
					char	*nd_cap = tgetstr("nd", NULL);
					ft_putstr(nd_cap);
					c_i++;
					cursor_pos++;
				}
			}
		}
		else
		{
			if (buff[0] == readline_vars.keys.enter)
			{
				*line = strdup(history_line[l_i].elements);
				if (history_line[l_i].used_size > 0)
				{
					t_char_vec	new_vec;
					initialize_vec_of_char(&new_vec);
					new_vec.add_set_of_elements_at_index(&new_vec, history_line[l_i].elements, 0);
					readline_vars.history.delete_element_at_index(&readline_vars.history, readline_vars.history.used_size - 1);
					readline_vars.history.add_new_element(&readline_vars.history, new_vec);

					if (old_history[l_i] != NULL)
					{
						t_char_vec	old_line;
						initialize_vec_of_char(&old_line);
						old_line.add_set_of_elements_at_index(&old_line, old_history[l_i], 0);
						readline_vars.history.delete_element_at_index(&readline_vars.history, l_i);
						readline_vars.history.add_new_element_at_index(&readline_vars.history, old_line, l_i);
					}
				}
				else
					readline_vars.history.delete_element_at_index(&readline_vars.history, readline_vars.history.used_size - 1);
				ft_putstr("\n");
				break ;
			}
			else if (buff[0] == readline_vars.keys.backspace)
			{
				if (c_i > 0)
				{
					c_i--;
					cursor_pos--;
					history_line[l_i].delete_element_at_index(&history_line[l_i], c_i);
					// ft_putstr(clear_line);
					clear_after_cursor(cursor_pos);
					ft_putstr(history_line[l_i].elements + c_i);
					move_cursor_to_colum(cursor_pos);
					// printf("{%s}\n", line[l_i].elements);
				}
			}
			else
				printf("[%d]\n", buff[0]);
		}
		// if (iscntrl(buff[0])) {
      	// 	printf("%d\r\n", buff[0]);
    	// } else {
      	// 	printf("%d ('%c')\r\n", buff[0], buff[0]);
    	// }
		buff[0] = '\0';
		buff[1] = '\0';
		buff[2] = '\0';
		buff[3] = '\0';
	}
	free(buff);
	free_array(old_history);
}

void	readline(char **line)
{
	struct termios	original_termios_state;
	static int		first_time = 1;
	char			*term_type = getenv("TERM");

	if (first_time)
	{
		initialize_vec_of_char_vec(&readline_vars.history);
		assign_keys(&readline_vars.keys);
	}
	tgetent(NULL, term_type);
	tcgetattr(STDIN_FILENO, &original_termios_state);
	enable_raw_mode();
	edit_line(line);
	disable_raw_mode(&original_termios_state);
	first_time = 0;
}
