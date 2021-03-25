# include "../minishell.h"

typedef struct          s_vars
{
    int                 backslash;
    int                 double_quotes;
    int                 single_quotes;
}                       t_vars;

int                     check_simple_word_syntax(char *token);