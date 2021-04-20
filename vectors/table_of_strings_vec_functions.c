#include "./vectors.h"

void	initialize_vec_content(t_vec *vec)
{
	vec->size = 2;
	vec->used_size = 0;
	vec->elements = malloc(sizeof(char*) * (vec->size) + 1);
	vec->add_new_element = add_new_element;
}

void	realloc_dynamic_table(t_vec *vec)
{
	int		i;
	char	**new_table;

	i = -1;
	new_table = malloc(sizeof(char*) * (vec->size + 1));
	while (++i < vec->used_size)
		new_table[i] = vec->elements[i];
	free(vec->elements);
	vec->elements = new_table;
}

void	add_new_element(t_vec *vec, char *element)
{
	if (vec->used_size == vec->size)
	{
		vec->size *= 2;
		realloc_dynamic_table(vec);
	}
	vec->elements[vec->used_size] = element;
	vec->elements[vec->used_size + 1] = NULL;
	vec->used_size += 1;
}
