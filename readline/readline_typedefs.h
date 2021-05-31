#ifndef READLINE_TYPEDEFS_H
# define READLINE_TYPEDEFS_H

# include "../vectors/vectors.h"
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef enum e_key
{
	none,
	waiting,
	up_arrow,
	down_arrow,
	left_arrow,
	right_arrow,
	enter,
	backspace,
	home,
	end,
	shift_right_arrow,
	shift_left_arrow,
	ctl_up_arrow,
	ctl_down_arrow,
	ctl_right_arrow,
	ctl_left_arrow,
	ctl_s,
	ctl_v,
	ctl_x,
	printable
}	t_key;

typedef enum e_print_method
{
	none,
	syntax_highlighting,
	
}	t_print_method;

typedef struct s_trie_node
{
	struct s_trie_node	**children;
	t_key				key;
}				t_trie_node;

typedef struct s_capability
{
	char		*mv_cursor_down_vertically;
	char		*mv_cursor_up_vertically;
	char		*mv_cursor_left;
	char		*mv_cursor_right;
	char		*mv_cursor_to_colm;
	char		*clear_line_after_cursor;
	char		*clear_lines_below;
	char		*make_cursor_invisible;
	char		*return_cursor_to_normal;
	char		*leave_standout_mode;
	char		*enter_standout_mode;
}				t_capability;

typedef struct s_rdline
{
	t_capability	capability;
	t_trie_node		*key_seq_trie;
	t_vchar_vec		history_vec;
	struct termios	original_termios_state;
	char			**old_history;
	char			*line;
	char			*prompt;
	int				tty_fd;
	int				prompt_len;
	int				curs_colm_pos;
	int				curs_row_pos;
	t_int_vec		old_curs_colm_pos_stack;
	t_int_vec		old_curs_row_pos_stack;
	int				printed_lines;
	int				width_of_screen;
	int				l_i;
	int				c_i;
	int				reverse_video_mode;
	char			*hilitd_txt;
	int				is_matched_history;
	int				matched_history_index;
	int				starting_hilitd_index;
	int				curr_hilitd_char_index;
	int				beg_hilitd_index;
	int				last_hilitd_index;
	int				starting_hilitd_colm;
	int				starting_hilitd_row;
	int				printing_method;
}					t_rdline;

#endif