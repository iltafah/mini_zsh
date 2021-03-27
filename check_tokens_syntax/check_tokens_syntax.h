# include "../minishell.h"

typedef struct          s_vars
{
    int                 backslash;
    int                 double_quotes;
    int                 single_quotes;
    int                 command;
    int                 redirection;
    int                 pipe;
    int                 error;
}                       t_vars;

void                     check_simple_word_syntax(char *token);