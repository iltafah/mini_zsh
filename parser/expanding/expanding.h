#ifndef EXPANDING_H
# define EXPANDING_H

# include "../../minishell.h"
# include "../usefull_functions/usefull_functions.h"

# define SPECIAL_SINGLE_QUOTES -1
# define SPECIAL_DOUBLE_QUOTES -2
# define SPECIAL_BACKSLASH -3

void		give_quotes_special_meaning(char *str);

#endif