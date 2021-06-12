#include "../vectors.h"

void	add_set_of_chars(t_char_vec *vec, char *str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		add_new_char(vec, str[i]);
		i++;
	}
}
