#include "expanding.h"

int		is_alpha(char c)
{
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

int		is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

char	*get_dollar_name(char *str, int *index_addr)
{
	int		i;
	int		len;
	int		start;
	char	*name;

	len = 0;
	start = *index_addr + 1;
	i = start;
	if (is_digit(str[i]))
	{
		i++;
		len++;
	}
	else
	{
		while (str[i] != '\0' && is_alpha(str[i]))
		{
			i++;
			len++;
		}
	}
	*index_addr = i;
	name = ft_substr(str, start, len);
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

void	expand_curr_var(char *str, int *i, t_char_vec *vec, t_env_table env)
{
	char		*name;
	char		*value;

	name = get_dollar_name(str, i);
	value = get_dollar_value(name, env);
	vec->add_set_of_elements_at_index(vec, value, vec->used_size);
	free(name);
}

void	expand_dollar_vars(char **arg_str, t_env_table env_table)
{
	int			i;
	t_char_vec	vec;
	t_quotes	quotes;

	i = 0;
	initialize_vec_of_char(&vec);
	initialize_quotes_vars(&quotes);
	while ((*arg_str)[i] != '\0')
	{
		if ((*arg_str)[i] == SPECIAL_SINGLE_QUOTES)
			open_and_close_single_quotes(&quotes);
		else if ((*arg_str)[i] == DOLLAR)
		{
			if (quotes.backslash == NONE && quotes.single_quotes == CLOSED)
			{
				expand_curr_var(*arg_str, &i, &vec, env_table);
				continue ;
			}	
		}
		does_backslash_exist((*arg_str)[i], &quotes);
		vec.add_new_element(&vec, (*arg_str)[i++]);
	}
	free(*arg_str);
	*arg_str = vec.elements;
}
