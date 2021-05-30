#ifndef GLOBAL_VARIABLES_H
# define GLOBAL_VARIABLES_H

# include "./readline/readline.h"
# include "./environment/environment.h"

typedef struct s_gvars
{
	t_rdline		rdl_vars;
	t_env_table		env_table;
}				t_gvars;

extern t_gvars		g_vars;

#endif