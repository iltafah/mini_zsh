#include "../vectors.h"

void	delete_last_char_vec(t_vchar_vec *vec)
{
	if (vec->used_size > 0)
	{
		free(vec->elements[vec->last_index].elements);
		vec->used_size -= 1;
		if (vec->used_size > 0)
			vec->last_index = vec->used_size - 1;
		else
			vec->last_index = 0;
		if (vec->size > 0 && vec->used_size < (vec->size / 4))
		{
			vec->size /= 2;
			realloc_vector_of_char_vec(vec);
		}
	}
}
