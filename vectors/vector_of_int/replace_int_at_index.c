#include "../vectors.h"

void	replace_int_at_index(t_int_vec *vec, int num, int index)
{
	if (index < 0 || index > vec->last_index)
		return ;
	vec->elements[index] = num;
}
