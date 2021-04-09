
# include "../minishell.h"
//char *treat_single_quotes(char **line, t_type *type);
int     treat_quotes(char *line, char sd_quote);
char    *get_pipe(char **line, t_type *type);
char    *get_semicolon(char **line, t_type *type);
char    *get_redirection(char **line, t_type *type);
char    *get_simple_word(char **line, t_type *type);


// t_node *create_pipline(void);
// void fill_cmd_node(t_node **curr_cmd_node);
// void fill_word_node(t_node **curr_word_node, char *word);
// void fill_pipeline(t_node **curr_pipeline_node);
// t_node **get_node(t_node **curr_node, int dir);
// t_node *create_single_node(void);