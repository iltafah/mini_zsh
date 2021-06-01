#ifndef READLINE_H
# define READLINE_H

# include "./readline_typedefs.h"
# include "../minishell.h"

# define CYN "\e[1;96m"
# define YEL "\e[1;93m"
// # define RED "\e[1;91m"
# define RED_MAX "\e[38;5;196m"
# define GRN "\e[1;92m"
# define PRP "\e[1;95m"
# define WHT "\e[1;97m"
# define GRY "\e[38;5;245m"
# define PNK "\e[38;5;200m"
# define ORN "\e[38;5;202m"
# define l_CYN "\e[38;5;159m"

# define SKIP continue

FILE		*fd;
FILE		*fd2;


enum e_bool {false, true};
enum e_restore {dont_restore, restore};
enum e_is_found {not_found, found};
enum e_is_on {off, on};


int			put_char(int c);
int			get_screen_width(void);
char		*get_prompt_name(void);
char		*read_line(char *prompt);
char		*get_curr_dir_name(void);
int			ft_strlen_utf8(char *str);
void		signals_handler(int sig_num);
int			check_if_cmd_exist(char *cmd);
void		sigwinch_handler(int sig_num);
void		move_left(t_rdline *rdl_vars);
void		move_right(t_rdline *rdl_vars);
t_trie_node	*initialize_key_seq_trie(void);
int			check_if_file_exist(char *file);
void		left_highlight(t_rdline *rdl_v);
void		load_history(t_rdline *rdl_vars);
void		right_highlight(t_rdline *rdl_v);
void		print_prompt(t_rdline *rdl_vars);
void		show_old_history(t_rdline *rdl_vars);
void		show_new_history(t_rdline *rdl_vars);
void		move_cursor_left(t_rdline *rdl_vars);
void		erase_suggestions(t_rdline *rdl_vars);
void		print_suggestions(t_rdline *rdl_vars);
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
t_char_vec	convert_string_to_char_vec(char *string);
void		move_down_vertically(t_rdline *rdl_vars);
void		save_curr_cursor_pos(t_rdline *rdl_vars);
void		cut_highlighted_text(t_rdline *rdl_vars);
void		past_highlighted_text(t_rdline *rdl_vars);
void		copy_highlighted_text(t_rdline *rdl_vars);
void		detect_screen_resizing(t_rdline *rdl_vars);
void		overwrite_history_file(t_rdline *rdl_vars);
void		print_curr_char(t_rdline *rdl_vars, char c);
void		start_highlighting_mode(t_rdline *rdl_vars);
void		clear_lines_below_cursor(t_rdline *rdl_vars);
void		move_to_beginning_of_line(t_rdline *rdl_vars);
void		move_cursor_up_vertically(t_rdline *rdl_vars);
void		erase_and_remove_curr_char(t_rdline *rdl_vars);
void		process_input(t_rdline *rdl_vars, char *prompt);
void		move_cursor_to_row(t_rdline *rdl_vars, int row);
void		insert_curr_line_to_history(t_rdline *rdl_vars);
void		move_cursor_down_vertically(t_rdline *rdl_vars);
void		clear_curr_line_after_cursor(t_rdline *rdl_vars);
void		move_cursor_end_of_prec_line(t_rdline *rdl_vars);
int			open_history_file(t_rdline *rdl_vars, int o_flag);
void		move_cursor_to_colum(t_rdline *rdl_vars, int col);
void		initialize_capabilities(t_capability *capability);
void		move_cursor_start_of_next_line(t_rdline *rdl_vars);
void		disable_raw_mode(struct termios old_termios_state);
void		clear_printed_lines(t_rdline *rdl_vars, int option);
void		quit_highlighting_mode(t_rdline *rdl_vars, int key);
void		move_cursor_to_end_of_printed_line(t_rdline *rdl_vars);
void		rdl_print_char(t_rdline *rdl_vars, char c, char *color);
char		**convert_history_vec_to_array(t_vchar_vec *history_vec);
void		determine_beg_last_highlighted_txt_indx(t_rdline *rdl_v);
void		clear_curr_line_after_and_below_cursor(t_rdline *rdl_vars);
void		add_empty_char_vec_to_history_vec(t_vchar_vec *history_vec);
void		print_after_cursor(t_rdline *rdl_vars, char *str, int option);
void		print_with_syntax_highlighting(t_rdline *rdl_vars, int option);
void		initialize_termios_struct(struct termios *original_termios_state);
void		move_cursor_to_colum_and_row(t_rdline *rdl_vars, int col, int row);
void		print_line_with_chosen_method(t_rdline *rdl, char *lin, int option);

#endif