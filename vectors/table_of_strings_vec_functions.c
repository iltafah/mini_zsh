#include "./vectors.h"

void initialize_vec_content(t_vec *vec)
{
	vec->size = 2;
	vec->used_size = 0;
	vec->elements = malloc(sizeof(char *) * (vec->size) + 1);
	vec->add_new_element = add_new_element;
	vec->add_new_element_at_index = add_new_element_at_index;
	vec->replace_element_at_index = replace_element_at_index;
	vec->delete_element_at_index = delete_element_at_index;
	vec->free = vector_free;
}

void realloc_vector(t_vec *vec)
{
	int i;
	char **new_table;

	i = -1;
	new_table = malloc(sizeof(char *) * (vec->size + 1));
	while (++i < vec->used_size)
		new_table[i] = vec->elements[i];
	free(vec->elements);
	vec->elements = new_table;
}

void	add_new_element(t_vec *vec, char *element)
{
	if (vec->used_size == vec->size)
	{
		vec->size *= 2;
		realloc_vector(vec);
	}
	vec->elements[vec->used_size] = ft_strdup(element);
	vec->elements[vec->used_size + 1] = NULL;
	vec->used_size += 1;
}

void replace_element_at_index(t_vec *vec, char *element, int index)
{
	if (index < 0 || index > vec->size)
		return ;
	vec->elements[index] = element;
}

void add_new_element_at_index(t_vec *vec, char *element, int index)
{
	char	*old_element;
	
	if (index < 0 || index > vec->size)
		return ;
	add_new_element(vec, element);
	old_element = vec->elements[index];
	replace_element_at_index(vec, element, index);
	replace_element_at_index(vec, old_element, vec->used_size);
}

void	delete_element_at_index(t_vec *vec, int index)
{
	if (index < 0 || index > vec->size)
		return ;
	free(vec->elements[index]);
	while (index <= vec->used_size)
	{
		vec->elements[index] = vec->elements[index + 1];
		index++;
	}
	vec->used_size -= 1;
	if (vec->size > 0 && vec->used_size < (vec->size / 4))
	{
		vec->size /= 2;
		realloc_vector(vec);
	}
}

void	vector_free(t_vec *vec)
{
	int		i;

	i = 0;
	while (i <= vec->used_size)
		free(vec->elements[i++]);
	free(vec);
}