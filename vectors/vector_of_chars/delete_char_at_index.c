#include "../vectors.h"

void	delete_char_at_index(t_char_vec *vec, int index)
{
	if (index < 0 || index > vec->used_size)
		return ;
	vec->elements[index] = '\0';
	while (index <= vec->used_size)
	{
		vec->elements[index] = vec->elements[index + 1];
		index++;
	}
	vec->used_size -= 1;
	if (vec->used_size > 0)
		vec->last_index = vec->used_size - 1;
	if (vec->size > 0 && vec->used_size < (vec->size / 4))
	{
		vec->size /= 2;
		realloc_char_vector(vec, vec->size);
	}
}
