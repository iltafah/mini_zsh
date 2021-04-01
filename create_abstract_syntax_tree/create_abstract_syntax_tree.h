#include "../minishell.h"

typedef struct s_vars
{
    int pipe_seq_node;
    int word_node;
    int simple_command_node;
    //int semicolon_token;
    //int pipe_token;
} t_vars;

typedef struct s_ast_ptrs
{
    t_node **cmd_line_node;
    t_node **curr_pipe_seq_node;
    t_node **curr_simple_cmd_node;
    t_node **curr_word_node;
} t_ast_ptrs;

t_node *create_single_node(t_tag tag);
t_node **get_node(t_node **curr_node, int dir);
t_node **get_cmd_line(void);
t_node **get_word_node(t_node **curr_node, int dir);
t_node **get_pipe_seq_node(t_node **curr_node, int dir);
t_node **get_simple_cmd_node(t_node **curr_node, int dir);
void fill_word_node(t_node **curr_word_node, char *word);
void fill_cmd_node(t_node **curr_cmd_node);
void fill_pipeline(t_node **curr_pipeline_node);