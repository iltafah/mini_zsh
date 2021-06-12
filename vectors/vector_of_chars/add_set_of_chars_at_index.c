#include "../vectors.h"

void	add_set_of_chars_at_index(t_char_vec *vec, char *str, int index)
{
	int		i;

	if (index < 0 || index > vec->used_size || str == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		add_new_char_at_index(vec, str[i], index++);
		i++;
	}
}
