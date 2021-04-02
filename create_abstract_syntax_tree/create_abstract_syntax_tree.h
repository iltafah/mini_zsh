#include "../minishell.h"

typedef struct s_node_state
{
    int pipe_seq_node;
    int word_node;
    int simple_command_node;
} t_state;

typedef struct s_ast_ptrs
{
    t_node **cmd_line_node;
    t_node **curr_pipe_seq_node;
    t_node **curr_simple_cmd_node;
    t_node **curr_word_node;
} t_ast_ptrs;

void    initialize_node_vars(t_state *vars);
void    initialize_ast_pointers(t_ast_ptrs *ast);
t_node  *create_single_node(t_tag tag);
t_node  **create_word_node(t_node **curr_node, int dir);
t_node  **create_pipe_seq_node(t_node **curr_node, int dir);
t_node  **create_simple_cmd_node(t_node **curr_node, int dir);
void    store_word_in_suitable_node(t_state state, t_ast_ptrs *ast, char *word);
void    store_redirection_data(t_ast_ptrs *ast, t_tokens **curr_token);