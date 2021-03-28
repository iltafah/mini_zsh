#include "../minishell.h"



t_node *create_single_node();
t_node **get_node(t_node **curr_node, int dir);
void fill_word_node(t_node **curr_word_node, char *word);
void fill_cmd_node(t_node **curr_cmd_node);
void fill_pipeline(t_node **curr_pipeline_node);