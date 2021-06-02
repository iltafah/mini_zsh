#include "./vectors.h"

void    initialize_vec_of_int(t_int_vec *vec)
{
	vec->size = 2;
	vec->used_size = 0;
	vec->last_index = 0;
	vec->elements = malloc(sizeof(int) * vec->size);
	vec->add_new_element = add_new_int;
	vec->add_new_element_at_index = add_new_int_at_index;
	vec->replace_element_at_index = replace_int_at_index;
	vec->delete_element_at_index = delete_int_at_index;
	vec->push_element = push_int;
	vec->pop_element = pop_int;
	vec->free = int_vector_free;
}

void    realloc_int_vector(t_int_vec *vec, int new_size)
{
	int     i;
	int    *new_array;

	i = -1;
	new_array = malloc(sizeof(int) * new_size);
	while (++i < vec->used_size)
		new_array[i] = vec->elements[i];
	free(vec->elements);
	vec->elements = new_array;
}

void	add_new_int(t_int_vec *vec, int num)
{
	if (vec->used_size == vec->size)
	{
		vec->size *= 2;
		realloc_int_vector(vec, vec->size);
	}
	vec->elements[vec->used_size] = num;
	vec->used_size += 1;
	if (vec->used_size > 0)
		vec->last_index = vec->used_size - 1;
}


void	delete_int_at_index(t_int_vec *vec, int index)
{
	if (index < 0 || index > vec->used_size)
		return ;
	vec->elements[index] = 0;
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
		realloc_int_vector(vec, vec->size);
	}
}

void    add_new_int_at_index(t_int_vec *vec, int num, int index)
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

void	push_int(t_int_vec *vec, int num)
{
	add_new_int_at_index(vec, num, 0);
}

void	pop_int(t_int_vec *vec, int *num_addr)
{
	if (vec->used_size > 0)
	{
		*num_addr = vec->elements[0];
		delete_int_at_index(vec, 0);
	}
}

void    replace_int_at_index(t_int_vec *vec, int num, int index)
{
	if (index < 0 || index > vec->last_index)
		return ;
	vec->elements[index] = num;
}

void	int_vector_free(t_int_vec *vec)
{
	free(vec->elements);
	vec->elements = NULL;
}