#include "../readline.h"

int	put_char(int c)
{
	int	len;

	len = write(1, &c, 1);
	return (len);
}
