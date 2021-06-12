#include "../vectors.h"

void	add_new_int_at_index(t_int_vec *vec, int num, int index)
{
	int		last_element;
	int		last_index;

	if (index < 0 || index > vec->size)
		return ;
	add_new_int(vec, num);
	last_index = vec->used_size - 1;
	last_element = vec->elements[last_index];
	while (last_index > index)
	{
		vec->elements[last_index] = vec->elements[last_index - 1];
		last_index--;
	}
	vec->elements[index] = last_element;
}
