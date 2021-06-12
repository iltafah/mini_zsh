#include "../vectors.h"

void	realloc_char_vector(t_char_vec *vec, int new_size)
{
	int		i;
	char	*new_string;

	i = -1;
	new_string = malloc(sizeof(char) * (new_size + 1));
	while (++i < vec->used_size)
		new_string[i] = vec->elements[i];
	new_string[i] = '\0';
	free(vec->elements);
	vec->elements = new_string;
}

void	char_vector_free(t_char_vec *vec)
{
	free(vec->elements);
	vec->elements = NULL;
}
