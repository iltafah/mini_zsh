#ifndef READLINE_H
# define READLINE_H

# include <sys/ioctl.h>
# include <signal.h>
# include "stdio.h"
# include "../vectors/vectors.h"

# define CYN "\e[1;96m"
# define YEL "\e[1;93m"
# define RED "\e[1;91m"
# define GRN "\e[1;92m"
# define PRP "\e[1;95m"
# define WHT "\e[1;97m"

typedef enum e_key {none, waiting, up_arrow, down_arrow, left_arrow,
right_arrow, enter, backspace, printable} t_key;

enum e_bool {false, true};
enum e_restore {dont_restore, restore};


typedef struct	s_trie_node
{
	t_key key;
	struct s_trie_node **children;	
}				t_trie_node;


typedef struct	s_capability
{
	char		*mv_cursor_down_vertically;
	char		*mv_cursor_up_vertically;
	char		*mv_cursor_left;
	char		*mv_cursor_right;
	char		*clear_lines_below;
}				t_capability;

typedef struct		s_rdline
{
	t_capability	capability;
	t_trie_node		*key_seq_trie;
	t_vchar_vec		history_vec;
	char			**old_history;
	char			*line;
	int				curr_dirc_len;
	int				curs_colm_pos;
	int				curs_colm_old_pos;
	int				curs_row_pos;
	int				curs_row_old_pos;
	int				printed_lines;
	int				width_of_screen;
	int				l_i;
	int				c_i;
}					t_rdline;


typedef struct termios t_termios;


typedef struct		s_gvars
{
	t_rdline		rdl_vars;
}					t_gvars;

t_gvars			g_vars;

void	read_line(char **line);
t_trie_node	*initialize_key_seq_trie(void);
int	get_key(t_trie_node *trie_root, char c);

#endif