#include "./minishell.h"

int	ft_strlen_utf8(char *str)
{
	int	byte;
	int	count;

	byte = 0;
	count = 0;
	while (str[byte])
	{
		if ((str[byte] & 0xc0) != 0x80)
			count++;
		byte++;
	}
	return (count);
}
