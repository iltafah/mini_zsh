#include "./create_abstract_syntax_tree.h"

void	set_dynamic_table_size(t_dynamic_table *dynamic_table)
{
	if (*dynamic_table->ptr == NULL)
	{
		dynamic_table->size = 2;
		dynamic_table->used_size = 0;
	}
	if (dynamic_table->used_size == dynamic_table->size)
		dynamic_table->size *= 2;
}

void	dynamic_table_join(t_dynamic_table *dynamic_table, char *word)
{
	int		i;
	char	**new_table;

	i = -1;
	set_dynamic_table_size(dynamic_table);
	new_table = malloc(sizeof(char*) * (dynamic_table->size + 1));
	while (++i < dynamic_table->used_size)
		new_table[i] = (*dynamic_table->ptr)[i];
	new_table[i++] = word;
	new_table[i] = NULL;
	if (*dynamic_table->ptr != NULL)
		free(*dynamic_table->ptr);
	dynamic_table->ptr = &new_table;
	dynamic_table->used_size += 1;
}

void	store_word_in_suitable_node(t_ast_vars *vars, char *word)
{
	get_suitable_nodes(vars->state, &vars->ast_ptrs);
	vars->dynamic_table.ptr = &((*vars->ast_ptrs.curr_data)->node.data.args);
	dynamic_table_join(&vars->dynamic_table, word);
	(*vars->ast_ptrs.curr_data)->node.data.args = *vars->dynamic_table.ptr;
}
