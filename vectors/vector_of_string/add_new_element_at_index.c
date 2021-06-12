#include "../vectors.h"

void	add_new_element_at_index(t_str_vec *vec, char *element, int index)
{
	char	*last_element;
	int		last_index;

	if (index < 0 || index > vec->size || element == NULL)
		return ;
	add_new_element(vec, element);
	last_index = vec->used_size - 1;
	last_element = vec->elements[last_index];
	while (last_index > index)
	{
		vec->elements[last_index] = vec->elements[last_index - 1];
		last_index--;
	}
	vec->elements[index] = last_element;
}
