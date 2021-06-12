#include "../readline.h"

int	check_if_file_exist(char *file)
{
	struct stat	buffer;
	int			does_exist;

	does_exist = stat(file, &buffer);
	if (does_exist == 0)
		return (EXIST);
	return (NONE);
}
