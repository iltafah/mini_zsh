#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include "stdlib.h"
# include "../vectors/vectors.h"
# include "../libft/libft.h"
/*
** ************************************************************************** **
									env table								
** ************************************************************************** **
*/

typedef struct s_env_table
{
	t_str_vec	name;
	t_str_vec	value;
} t_env_table;

/*
** ************************************************************************** **
** ************************************************************************** **
*/

char    **convert_env_table_to_array(t_env_table env_table);
void    create_env_table(t_env_table *env_table, char **env);

#endif