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

void                    check_simple_word_syntax(char *token);
void                    remember_last_token(t_vars *vars, t_type token);
void                    check_pipe_token_order(t_vars *vars);
void                    check_semicolon_token_order(t_vars *vars);
void                    check_redirection_token_order(t_vars *vars);
void                    check_newline_token_order(t_vars *vars);
void                    check_word_token_order(t_vars *vars, char *token);
