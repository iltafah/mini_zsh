#ifndef EXPANDING_H
# define EXPANDING_H

# include "../parser.h"

void	give_quotes_special_meaning(char *str);
void    expand_dollar_vars(char **str_addr, t_env_table env_table);
void	split_element_to_args(t_str_vec *vec, int *index);
void	remove_special_quotes(char **str_addr);


#endif