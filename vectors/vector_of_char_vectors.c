#include "./vectors.h"
#include <stdio.h>

void initialize_vec_of_char_vec(t_vchar_vec *vec)
{
	vec->size = 2;
	vec->used_size = 0;
	vec->last_index = 0;
	vec->elements = malloc(sizeof(t_char_vec) * (vec->size));
	vec->add_new_element = add_new_char_vec;
	vec->delete_element_at_index = delete_char_vec_at_index;
	vec->add_new_element_at_index = add_new_char_vec_at_index;
	// vec->replace_element_at_index = replace_char_vec_at_index;
	// vec->delete_element_at_index = delete_char_vec_at_index;
	vec->free = char_vec_vector_free;
}

void realloc_vector_of_char_vec(t_vchar_vec *vec)
{
	int			i;
	t_char_vec	*new_table;

	i = -1;
	new_table = malloc(sizeof(t_char_vec) * vec->size);
	while (++i < vec->used_size)
		new_table[i] = vec->elements[i];
	free(vec->elements);
	vec->elements = new_table;
}

void	add_new_char_vec(t_vchar_vec *vec, t_char_vec element)
{
	if (vec->used_size == vec->size)
	{
		vec->size *= 2;
		realloc_vector_of_char_vec(vec);
	}
	vec->elements[vec->used_size] = element;
	vec->used_size += 1;
	if (vec->used_size > 0)
		vec->last_index = vec->used_size - 1;
}

// void replace_char_vec_at_index(t_vchar_vec *vec, t_char_vec element, int index)
// {
// 	if (index < 0 || index > vec->size)
// 		return ;
// 	vec->elements[index] = element;
// }

void	add_new_char_vec_at_index(t_vchar_vec *vec, t_char_vec elem, int index)
{
	t_char_vec	last_element;
	int			last_index;
	int			i;

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

void	delete_char_vec_at_index(t_vchar_vec *vec, int index)
{
	if (index < 0 || index > vec->size)
		return ;
	free(vec->elements[index].elements);
	while (index < vec->used_size)
	{
		vec->elements[index] = vec->elements[index + 1];
		index++;
	}
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

void	delete_last_char_vec(t_vchar_vec *vec)
{
	int		last_index;

	last_index = 0;
	if ((vec->used_size - 1) > 0)
		last_index = vec->used_size - 1;
	if (vec->used_size > 0)
	{
		free(vec->elements[last_index].elements);
		vec->used_size -= 1;
		vec->last_index = vec->used_size - 1;
		if (vec->size > 0 && vec->used_size < (vec->size / 4))
		{
			vec->size /= 2;
			realloc_vector_of_char_vec(vec);
		}
	}
}

void	char_vec_vector_free(t_vchar_vec *vec)
{
	int		i;

	i = 0;
	while (i < vec->used_size)
		free(vec->elements[i++].elements);
	free(vec->elements);
}