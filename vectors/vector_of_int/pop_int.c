#include "../vectors.h"

void	pop_int(t_int_vec *vec, int *num_addr)
{
	if (vec->used_size > 0)
	{
		*num_addr = vec->elements[0];
		delete_int_at_index(vec, 0);
	}
}
