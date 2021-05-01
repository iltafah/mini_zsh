#ifndef READLINE_H
# define READLINE_H

# include "../vectors/vectors.h"

# define CYN "\e[1;96m"
# define YEL "\e[1;93m"
# define RED "\e[1;91m"
# define GRN "\e[1;92m"
# define PRP "\e[1;95m"
# define WHT "\e[1;97m"

typedef struct	s_keys
{
	char	*up_arrow;
	char	*down_arrow;
	char	*left_arrow;
	char	*right_arrow;
	char	enter;
	char	backspace;
}				t_keys;


// typedef struct	s_capability
// {

// }				t_capability;


typedef struct		s_readline
{
	t_vec_vec_char	history;
	t_keys			keys;
	// t_capability	capability
}					t_readline;

t_readline			readline_vars;

void	readline(char **line);

#endif