#include "./create_abstract_syntax_tree.h"

// void initialize_args_vector(t_dynamic_table *dynamic_table)
// {
// 	(*dynamic_table->ptr) = malloc(sizeof(char *) * (2 + 1));
// 	dynamic_table->size = 2;
// 	dynamic_table->used_size = 0;
// }

// void realloc_args_dynamic_table(t_dynamic_table *dynamic_table)
// {
// 	int i;
// 	char **new_table;

// 	new_table = malloc(sizeof(char *) * (dynamic_table->size + 1));
// 	i = -1;
// 	while (++i < dynamic_table->used_size)
// 		new_table[i] = (*dynamic_table->ptr)[i];
// 	if (*dynamic_table->ptr != NULL)
// 		free(*dynamic_table->ptr);
// 	dynamic_table->ptr = &new_table;
// }

// void dynamic_table_join(t_dynamic_table *dynamic_table, char *word)
// {
// 	if (dynamic_table->used_size == dynamic_table->size)
// 	{
// 		dynamic_table->size *= 2;
// 		realloc_args_dynamic_table(dynamic_table);
// 	}
// 	(*dynamic_table->ptr)[dynamic_table->used_size] = word;
// 	(*dynamic_table->ptr)[dynamic_table->used_size + 1] = NULL;
// 	dynamic_table->used_size += 1;
// }

void store_word_in_suitable_node(t_ast_vars *vars, char *word)
{
	t_vec	*args_vec;

	get_suitable_nodes(vars->state, &vars->ast_ptrs);
	args_vec = &((*vars->ast_ptrs.curr_data)->node.data.args_vec);
	args_vec->add_new_element(args_vec, word);
	// vars->dynamic_table.ptr = &((*vars->ast_ptrs.curr_data)->node.data.args);
	// if ((*vars->dynamic_table.ptr) == NULL)
		// initialize_args_vector(&vars->dynamic_table);
	// dynamic_table_join(&vars->dynamic_table, word);
	// (*vars->ast_ptrs.curr_data)->node.data.args = *vars->dynamic_table.ptr;
}
