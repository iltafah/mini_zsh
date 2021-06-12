#include "../vectors.h"

void	add_new_char_vec(t_vchar_vec *vec, t_char_vec element)
{
	if (vec->used_size == vec->size)
	{
		vec->size *= 2;
		realloc_vector_of_char_vec(vec);
	}
	vec->elements[vec->used_size] = element;
	vec->used_size += 1;
	if (vec->used_size > 0)
		vec->last_index = vec->used_size - 1;
}
