#include "readline.h"

char	*get_curr_dir_name(void)
{
	char	*curr_dir;
	int		keep_index;
	int		len;
	int		i;

	i = 0;
	len = 0;
	keep_index = 0;
	curr_dir = getcwd(NULL, 0);
	while (curr_dir[i] != '\0')
	{
		if (curr_dir[i] == '/')
			keep_index = i + 1;
		i++;
	}
	return (curr_dir + keep_index);
}
