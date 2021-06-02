#include "./minishell.h"
#include "errno.h"

char	*get_curr_dir_name(void)
{
	char	*full_path;
	char	*curr_dir;
	int		keep_index;
	int		len;
	int		i;

	i = 0;
	len = 0;
	keep_index = 0;
	full_path = getcwd(NULL, 0);
	if (full_path != NULL)
	{
		while (full_path[i] != '\0')
		{
			if (full_path[i] == '/')
				keep_index = i + 1;
			i++;
		}
		curr_dir = ft_strdup(full_path + keep_index);
		free(full_path);
		return (curr_dir);
	}
	return (NULL);
}
