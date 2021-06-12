#include "../vectors.h"

void	realloc_vector(t_str_vec *vec)
{
	int		i;
	char	**new_table;

	i = -1;
	new_table = malloc(sizeof(char *) * (vec->size + 1));
	while (++i < vec->used_size)
		new_table[i] = vec->elements[i];
	free(vec->elements);
	vec->elements = new_table;
}

void	vector_free(t_str_vec *vec)
{
	int		i;

	i = 0;
	while (i < vec->used_size)
		free(vec->elements[i++]);
	free(vec->elements);
}
