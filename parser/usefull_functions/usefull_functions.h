
typedef struct          s_quotes
{
    int                 backslash;
    int                 double_quotes;
    int                 single_quotes;
}                       t_quotes;

#define CLOSED 0
#define OPEND 1

#define NONE 0
#define EXIST 1

void	initialize_quotes_vars(t_quotes *quotes);
void    open_and_close_double_quotes(t_quotes *quotes);
void    open_and_close_single_quotes(t_quotes *quotes);