#include "expanding.h"

int		is_alpha(char c)
{
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

char	*get_dollar_name(char *str, int *index_addr)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] != '\0' && is_alpha(str[i]))
		i++;
	*index_addr += (i + 1);
	name = ft_substr(str, 0, i);
	return (name);
}

char	*get_dollar_value(char *name, t_env_table env_table)
{
	int			i;
	char		*value;
	t_str_vec	*name_vec;
	t_str_vec	*value_vec;

	if (name == NULL)
		return NULL;
	i = 0;
	value = NULL;
	name_vec = &env_table.name;
	value_vec = &env_table.value;
	while (name_vec->elements[i])
	{
		if (strcmp(name, name_vec->elements[i]) == 0)
			value = value_vec->elements[i];
		i++;
	}
	return (value);
}

void	expand_dollar_vars(char **str_addr, t_env_table env_table)
{
	int			i;
	char		*name;
	char		*value;
	char		*old_str;
	t_char_vec	new_str;

	i = 0;
	old_str = *str_addr;
	initialize_vec_of_char(&new_str);
	while (old_str[i] != '\0')
	{
		if (old_str[i] == DOLLAR)
		{
			name = get_dollar_name(old_str + i + 1, &i);
			value = get_dollar_value(name, env_table);
			new_str.add_set_of_elements_at_index(&new_str, value, new_str.used_size);
			free(name);
		}
		else
			new_str.add_new_element(&new_str, old_str[i++]);
	}
	free(*str_addr);
	*str_addr = new_str.elements;
}
