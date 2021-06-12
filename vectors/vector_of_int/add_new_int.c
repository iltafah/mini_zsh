#include "../vectors.h"

void	add_new_int(t_int_vec *vec, int num)
{
	if (vec->used_size == vec->size)
	{
		vec->size *= 2;
		realloc_int_vector(vec, vec->size);
	}
	vec->elements[vec->used_size] = num;
	vec->used_size += 1;
	if (vec->used_size > 0)
		vec->last_index = vec->used_size - 1;
}
