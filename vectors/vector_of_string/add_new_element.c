#include "../vectors.h"

void	add_new_element(t_str_vec *vec, char *element)
{
	if (vec->used_size == vec->size)
	{
		vec->size *= 2;
		realloc_vector(vec);
	}
	vec->elements[vec->used_size] = element;
	vec->elements[vec->used_size + 1] = NULL;
	vec->used_size += 1;
}
