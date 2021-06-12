#include "../vectors.h"

void	initialize_vec_of_char(t_char_vec *vec)
{
	vec->size = 2;
	vec->used_size = 0;
	vec->last_index = 0;
	vec->elements = malloc(sizeof(char) * (vec->size) + 1);
	vec->elements[0] = '\0';
	vec->add_new_element = add_new_char;
	vec->add_set_of_elements = add_set_of_chars;
	vec->add_new_element_at_index = add_new_char_at_index;
	vec->add_set_of_elements_at_index = add_set_of_chars_at_index;
	vec->replace_element_at_index = replace_char_at_index;
	vec->delete_element_at_index = delete_char_at_index;
	vec->free = char_vector_free;
}
