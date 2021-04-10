#include "../minishell.h"

typedef struct		s_node_state
{
    int				pipe_seq_node;
    int				word_node;
    int				simple_command_node;
}					t_state;

typedef struct		s_ast_ptrs
{
    t_ast			**cmd_line;
    t_ast			**curr_pipe_seq;
    t_ast			**curr_simple_cmd;
    t_ast			**curr_data;
}					t_ast_ptrs;

typedef	struct		s_dynamic_table
{
	int				size;
	int				used_size;
	char			***ptr;
}					t_dynamic_table;


typedef struct		s_ast_vars
{
	t_ast_ptrs		ast_ptrs;
	t_state			state;
	t_dynamic_table	dynamic_table;
}					t_ast_vars;


t_ast  	*create_single_node(t_tag tag);
t_ast  	**create_data_node(t_ast **curr_node, int dir);
t_ast  	**create_pipe_seq_node(t_ast **curr_node, int dir);
t_ast  	**create_simple_cmd_node(t_ast **curr_node, int dir);
void	initialize_ast_vars(t_ast_vars *ast);
void	initialize_node_states(t_state *state);
void    store_word_in_suitable_node(t_ast_vars	*vars, char *word);
void    store_redirection_data(t_ast_vars *vars, t_tokens **curr_token);
void	dynamic_table_join(t_dynamic_table *dynamic_table, char *word);