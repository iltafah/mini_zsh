#include "../vectors.h"

void	add_new_char_vec_at_index(t_vchar_vec *vec, t_char_vec elem, int index)
{
	t_char_vec	last_element;
	int			last_index;

	if (index < 0 || index > vec->size)
		return ;
	add_new_char_vec(vec, elem);
	last_index = vec->used_size - 1;
	last_element = vec->elements[last_index];
	while (last_index > index)
	{
		vec->elements[last_index] = vec->elements[last_index - 1];
		last_index--;
	}
	vec->elements[index] = last_element;
}
