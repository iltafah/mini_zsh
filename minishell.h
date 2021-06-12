#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

# include "./vectors/vectors.h"
# include "./parser/parser.h"
# include "./libft/libft.h"
# include "./freeing_time/freeing_time.h"
# include "./get_next_line/get_next_line.h"
# include "./readline/readline.h"

typedef struct s_gvars
{
	t_rdline		rdl_vars;
	t_env_table		env_table;
}				t_gvars;

extern t_gvars		g_vars;

t_gvars				g_vars;

char	*get_prompt_name(void);
char	*get_curr_dir_name(void);
int		ft_strlen_utf8(char *str);

#endif
