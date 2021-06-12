#include "../vectors.h"

void	realloc_int_vector(t_int_vec *vec, int new_size)
{
	int		i;
	int		*new_array;

	i = -1;
	new_array = malloc(sizeof(int) * new_size);
	while (++i < vec->used_size)
		new_array[i] = vec->elements[i];
	free(vec->elements);
	vec->elements = new_array;
}

void	int_vector_free(t_int_vec *vec)
{
	free(vec->elements);
	vec->elements = NULL;
}
