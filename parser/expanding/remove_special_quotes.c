#include "./expanding.h"

int     is_it_special_quotes(char c)
{
    return (c == SPECIAL_BACKSLASH
        || c == SPECIAL_DOUBLE_QUOTES
        || c == SPECIAL_SINGLE_QUOTES);
}

void	remove_special_quotes(char **str_addr)
{
	int			i;
	char		*old_str;
	t_char_vec	new_str;

	i = 0;
	old_str = *str_addr;
	initialize_vec_of_char(&new_str);
	while(old_str[i] != '\0')
	{
		if (is_it_special_quotes(old_str[i]) == FALSE)
			new_str.add_new_element(&new_str, old_str[i]);
		i++;
	}
    free(*str_addr);
	*str_addr = new_str.elements;
}
