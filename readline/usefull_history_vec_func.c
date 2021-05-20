#include "./readline.h"

void	add_empty_char_vec_to_history_vec(t_vchar_vec *history_vec)
{
	t_char_vec	char_vec;

	initialize_vec_of_char(&char_vec);
	history_vec->add_new_element(history_vec, char_vec);
}

char	**convert_history_vec_to_array(t_vchar_vec *history_vec)
{
	int			i;
	char		**array;
	t_char_vec	*line;

	i = 0;
	line = history_vec->elements;
	array = malloc(sizeof(char *) * history_vec->used_size + 1);
	while (i < history_vec->used_size)
	{
		array[i] = strdup(line[i].elements);
		i++;
	}
	array[i] = NULL;
	return (array);
}
