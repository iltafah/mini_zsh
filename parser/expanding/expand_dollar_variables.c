/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:32:55 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:33:00 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

char	*get_dollar_name(char *str, int *index_addr)
{
	int		i;
	int		len;
	int		start;
	char	*name;

	len = 0;
	start = *index_addr + 1;
	i = start;
	if (ft_isdigit(str[i]) || str[i] == '?')
	{
		i++;
		len++;
	}
	else
	{
		while (str[i] != '\0' &&
			(ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
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

	if (name[0] == '\0')
		value = ft_strdup("$");
	else if (name[0] == '?')
		value = convert_int_to_str(g_vars.last_err_num);
	else
	{
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
	}
	g_vars.last_err_num = 0;
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
		vec.add_new_element(&vec, (*arg_str)[i]);
		i++;
	}
	free(*arg_str);
	*arg_str = vec.elements;
}
