#ifndef READLINE_H
# define READLINE_H

# include <sys/ioctl.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../vectors/vectors.h"
# include "../freeing_time/freeing_time.h"

# define CYN "\e[1;96m"
# define YEL "\e[1;93m"
# define RED "\e[1;91m"
# define GRN "\e[1;92m"
# define PRP "\e[1;95m"
# define WHT "\e[1;97m"
# define GRY "\e[38;5;245m"
FILE		*fd;

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

enum e_bool {false, true};
enum e_restore {dont_restore, restore};

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
}				t_capability;

typedef struct s_rdline
{
	t_capability	capability;
	t_trie_node		*key_seq_trie;
	t_vchar_vec		history_vec;
	char			**old_history;
	char			*line;
	char			*prompt;
	int				tty_fd;
	int				prompt_len;
	int				curs_colm_pos;
	int				curs_colm_old_pos;
	int				curs_row_pos;
	int				curs_row_old_pos;
	int				printed_lines;
	int				width_of_screen;
	int				l_i;
	int				c_i;
	int				reverse_video_mode;
	char			*hilitd_txt;
	int				starting_hilitd_index;
	int				curr_hilitd_char_index;
	int				beg_hilitd_index;
	int				last_hilitd_index;
	int				starting_hilitd_colm;
	int				starting_hilitd_row;
}					t_rdline;

typedef struct s_gvars
{
	t_rdline		rdl_vars;
}				t_gvars;

t_gvars		g_vars;
void		print_suggestions(t_rdline *rdl_vars);
int			put_char(int c);
int			get_screen_width(void);
char		*get_prompt_name(void);
void		read_line(char **line);
char		*get_curr_dir_name(void);
int			ft_strlen_utf8(char *str);
void		sigwinch_handler(int sig_num);
void		move_left(t_rdline *rdl_vars);
void		move_right(t_rdline *rdl_vars);
t_trie_node	*initialize_key_seq_trie(void);
void		left_highlight(t_rdline *rdl_v);
void		right_highlight(t_rdline *rdl_v);
void		print_prompt(t_rdline *rdl_vars);
void		show_old_history(t_rdline *rdl_vars);
void		show_new_history(t_rdline *rdl_vars);
void		move_cursor_left(t_rdline *rdl_vars);
void		move_to_next_word(t_rdline *rdl_vars);
void		move_cursor_right(t_rdline *rdl_vars);
void		move_to_prec_word(t_rdline *rdl_vars);
void		move_up_vertically(t_rdline *rdl_vars);
void		update_cursor_data(t_rdline *rdl_vars);
void		restore_cursor_pos(t_rdline *rdl_vars);
void		put_colorful_char(char c, char *color);
void		move_to_end_of_line(t_rdline *rdl_vars);
int			get_key(t_trie_node *trie_root, char c);
void		initialize_rdl_vars(t_rdline *rdl_vars);
void		move_down_vertically(t_rdline *rdl_vars);
void		save_curr_cursor_pos(t_rdline *rdl_vars);
void		cut_highlighted_text(t_rdline *rdl_vars);
void		past_highlighted_text(t_rdline *rdl_vars);
void		copy_highlighted_text(t_rdline *rdl_vars);
void		print_curr_char(t_rdline *rdl_vars, char c);
void		clear_lines_below_cursor(t_rdline *rdl_vars);
void		move_to_beginning_of_line(t_rdline *rdl_vars);
void		move_cursor_up_vertically(t_rdline *rdl_vars);
void		turn_on_reverse_video_mode(t_rdline *rdl_vars);
void		process_input(char **line, t_rdline *rdl_vars);
void		erase_and_remove_curr_char(t_rdline *rdl_vars);
void		move_cursor_to_row(t_rdline *rdl_vars, int row);
void		insert_curr_line_to_history(t_rdline *rdl_vars);
void		move_cursor_down_vertically(t_rdline *rdl_vars);
void		clear_curr_line_after_cursor(t_rdline *rdl_vars);
void		move_cursor_end_of_prec_line(t_rdline *rdl_vars);
void		move_cursor_to_colum(t_rdline *rdl_vars, int col);
void		initialize_capabilities(t_capability *capability);
void		move_cursor_start_of_next_line(t_rdline *rdl_vars);
void		clear_printed_lines(t_rdline *rdl_vars, int option);
void		rdl_print_char(t_rdline *rdl_vars, char c, char *color);
void		turn_off_reverse_video_mode(t_rdline *rdl_vars, int key);
char		**convert_history_vec_to_array(t_vchar_vec *history_vec);
void		determine_beg_last_highlighted_txt_indx(t_rdline *rdl_v);
void		clear_curr_line_after_and_below_cursor(t_rdline *rdl_vars);
void		add_empty_char_vec_to_history_vec(t_vchar_vec *history_vec);
void		print_after_cursor(t_rdline *rdl_vars, char *str, int option);
void		initialize_termios_struct(struct termios *original_termios_state);
void		move_cursor_to_colum_and_row(t_rdline *rdl_vars, int col, int row);

#endif