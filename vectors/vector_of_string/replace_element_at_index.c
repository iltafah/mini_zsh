#include "../vectors.h"

void	replace_element_at_index(t_str_vec *vec, char *element, int index)
{
	if (index < 0 || index > vec->size)
		return ;
	vec->elements[index] = element;
}
