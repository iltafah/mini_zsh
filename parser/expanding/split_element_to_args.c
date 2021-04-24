#include "./expanding.h" 

void	get_splitted_arg_and_insert_it(char **arg, t_str_vec *args_vec, int i)
{
	t_char_vec	splitted_arg;
	
	initialize_vec_of_char(&splitted_arg);
	while (**arg != ' ' && **arg != '\0')
	{
		if (**arg == SPECIAL_DOUBLE_QUOTES)
		{
			(*arg)++;
			while (**arg != SPECIAL_DOUBLE_QUOTES && **arg != '\0')
			{
				if (**arg != SPECIAL_BACKSLASH)
					splitted_arg.add_new_element(&splitted_arg, **arg);	
				(*arg)++;
			}
		}
		else if (**arg != SPECIAL_SINGLE_QUOTES && **arg != SPECIAL_BACKSLASH)
			splitted_arg.add_new_element(&splitted_arg, **arg);
		(*arg)++;
	}
	args_vec->add_new_element_at_index(args_vec, splitted_arg.elements, i);
}

void	split_element_to_args(t_str_vec *vec, int *index)
{
	int			i;
	char		*arg;
	
	i = *index;
	arg = vec->elements[i];
	while (*arg != '\0')
	{
		if (*arg == ' ')
			arg++;
		else
			get_splitted_arg_and_insert_it(&arg, vec, i++);
	}
	vec->delete_element_at_index(vec, i);
	*index = i;
}
