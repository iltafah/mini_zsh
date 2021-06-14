/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:32:55 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/14 21:23:39 by iltafah          ###   ########.fr       */
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

	i = 0;
	value = NULL;
	if (name[0] == '?')
		value = convert_int_to_str(g_vars.last_err_num);
	else
	{
		name_vec = &env_table.name;
		value_vec = &env_table.value;
		while (name_vec->elements[i])
		{
			if (strcmp(name, name_vec->elements[i]) == 0)
				value = value_vec->elements[i];
			i++;
		}
	}
	return (value);
}

void	expand_unquoted_var(char *str, int *i, t_char_vec *vec, t_env_table env)
{
	char		*name;
	char		*value;

	if (str[*i + 1] != '\0')
	{
		name = get_dollar_name(str, i);
		value = get_dollar_value(name, env);
		vec->add_set_of_elements_at_index(vec, value, vec->used_size);
		free(name);
	}
	else
	{
		*i += 1;
		vec->add_set_of_elements_at_index(vec, "$", vec->used_size);
	}
}

void	expand_quoted_var(char *str, int *i, t_char_vec *vec, t_env_table env)
{
	char		*name;
	char		*value;

	if (str[*i + 1] != SPECIAL_DOUBLE_QUOTES && str[*i + 1] != SPECIAL_SINGLE_QUOTES
			&& str[*i + 1] != DOUBLE_QUOTES && str[*i + 1] != SINGLE_QUOTES)
	{
		name = get_dollar_name(str, i);
		value = get_dollar_value(name, env);
		vec->add_set_of_elements_at_index(vec, value, vec->used_size);
		free(name);
	}
	else
	{
		*i += 1;
		vec->add_set_of_elements_at_index(vec, "$", vec->used_size);
	}
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
		if ((*arg_str)[i] == SPECIAL_SINGLE_QUOTES || (*arg_str)[i] == SPECIAL_DOUBLE_QUOTES)
			open_and_close_quotes((*arg_str)[i], &quotes);
		else if ((*arg_str)[i] == DOLLAR)
		{
			if (quotes.double_quotes == OPEND)
			{
				expand_quoted_var(*arg_str, &i, &vec, env_table);
				continue ;
			}
			else if (quotes.backslash == NONE && quotes.single_quotes == CLOSED)
			{
				expand_unquoted_var(*arg_str, &i, &vec, env_table);
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
