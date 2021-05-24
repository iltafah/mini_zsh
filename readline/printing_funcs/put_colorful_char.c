#include "../readline.h"

void	put_colorful_char(char c, char *color)
{
	write(1, color, ft_strlen(color));
	put_char(c);
}
