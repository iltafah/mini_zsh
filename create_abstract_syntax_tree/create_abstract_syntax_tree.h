#include "../minishell.h"

typedef struct		s_node_state
{
    int pipe_seq_node;
    int word_node;
    int simple_command_node;
}					t_state;

typedef struct		s_ast_ptrs
{
    t_ast **cmd_line_node;
    t_ast **curr_pipe_seq_node;
    t_ast **curr_simple_cmd_node;
    t_ast **curr_word_node;
}					t_ast_ptrs;

typedef	struct		s_dynamic_table
{
	int				size;
	int				used_size;
	char			***table_ptr;
}					t_dynamic_table;


typedef struct		s_ast_vars
{
	t_ast_ptrs		ast_ptrs;
	t_state			state;
	t_dynamic_table	dynamic_table;
}					t_ast_vars;


void    initialize_node_vars(t_state *vars);
void    initialize_ast_pointers(t_ast_ptrs *ast);
t_ast  *create_single_node(t_tag tag);
t_ast  **create_word_node(t_ast **curr_node, int dir);
t_ast  **create_pipe_seq_node(t_ast **curr_node, int dir);
t_ast  **create_simple_cmd_node(t_ast **curr_node, int dir);
void    store_word_in_suitable_node(t_ast_vars	*vars, char *word);
void    store_redirection_data(t_ast_ptrs *ast, t_tokens **curr_token);