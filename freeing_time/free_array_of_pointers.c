#include "./freeing_time.h"

void	free_array(char ***array_addr)
{
	int		i;
	char	**array;

	i = 0;
	array = *array_addr;
	while (array[i])
		free(array[i++]);
	free(*array_addr);
	*array_addr = NULL;
}
