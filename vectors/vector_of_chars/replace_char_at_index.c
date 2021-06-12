#include "../vectors.h"

void	replace_char_at_index(t_char_vec *vec, char c, int index)
{
	if (index < 0 || index > vec->size)
		return ;
	vec->elements[index] = c;
}
