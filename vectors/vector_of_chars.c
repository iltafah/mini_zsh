#include "./vectors.h"

void    initialize_vec_of_char(t_char_vec *vec)
{
	vec->size = 2;
	vec->used_size = 0;
	vec->elements = malloc(sizeof(char) * (vec->size) + 1);
	vec->add_new_element = add_new_char;
	vec->add_new_element_at_index = add_new_char_at_index;
	vec->replace_element_at_index = replace_char_at_index;
	vec->delete_element_at_index = delete_char_at_index;
	vec->free = char_vector_free;
}

void    realloc_char_vector(t_char_vec *vec)
{
	int     i;
	char    *new_string;

	i = -1;
	new_string = malloc(sizeof(char) * (vec->size + 1));
	while (++i < vec->used_size)
		new_string[i] = vec->elements[i];
	free(vec->elements);
	vec->elements = new_string;
}

void	add_new_char(t_char_vec *vec, char c)
{
	if (vec->used_size == vec->size)
	{
		vec->size *= 2;
		realloc_char_vector(vec);
	}
	vec->elements[vec->used_size] = c;
	vec->elements[vec->used_size + 1] = '\0';
	vec->used_size += 1;
}

void	delete_char_at_index(t_char_vec *vec, int index)
{
	if (index < 0 || index > vec->size)
		return ;
	vec->elements[index] = '\0';
	while (index <= vec->used_size)
	{
		vec->elements[index] = vec->elements[index + 1];
		index++;
	}
	vec->used_size -= 1;
	if (vec->size > 0 && vec->used_size < (vec->size / 4))
	{
		vec->size /= 2;
		realloc_char_vector(vec);
	}
}

void    add_new_char_at_index(t_char_vec *vec, char c, int index)
{
	char	last_element;
	int		last_index;
	int		i;

	if (index < 0 || index > vec->size)
		return ;
	add_new_char(vec, c);
	last_index = vec->used_size - 1;
	last_element = vec->elements[last_index];
	while (last_index > index)
	{
		vec->elements[last_index] = vec->elements[last_index - 1];
		last_index--;
	}
	vec->elements[index] = last_element;
}

void    replace_char_at_index(t_char_vec *vec, char c, int index)
{
	if (index < 0 || index > vec->size)
		return ;
	vec->elements[index] = c;
}

void	char_vector_free(t_char_vec *vec)
{
	free(vec);
}