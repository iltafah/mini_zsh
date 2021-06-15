/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:32:55 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/15 13:48:05 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

char	*get_dollar_name(char *str, int *index_addr)
{
	int		i;
	int		len;
	int		start;
	char	*name;

	start = *index_addr + 1;
	i = start;
	len = 0;
	if (ft_isdigit(str[i]) || str[i] == '?')
	{
		i++;
		len++;
	}
	else
	{
		while (str[i] != '\0'
			&& (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
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

	if (str[*i + 1] != '\0' && str[*i + 1] != SP_BACKSLASH
		&& str[*i + 1] != BACKSLASH)
	{
		name = get_dollar_name(str, i);
		value = get_dollar_value(name, env);
		vec->add_set_of_elements_at_index(vec, value, vec->used_size);
		free(name);
	}
	else
		vec->add_set_of_elements_at_index(vec, "$", vec->used_size);
}

void	expand_quoted_var(char *str, int *i, t_char_vec *vec, t_env_table env)
{
	char		*name;
	char		*value;

	if (str[*i + 1] != SP_DOUBLE_QUOTES && str[*i + 1] != SP_SINGLE_QUOTES
		&& str[*i + 1] != DOUBLE_QUOTES && str[*i + 1] != SINGLE_QUOTES
		&& str[*i + 1] != SP_BACKSLASH && str[*i + 1] != BACKSLASH
		&& str[*i + 1] != ' ')
	{
		name = get_dollar_name(str, i);
		value = get_dollar_value(name, env);
		vec->add_set_of_elements_at_index(vec, value, vec->used_size);
		free(name);
	}
	else
		vec->add_set_of_elements_at_index(vec, "$", vec->used_size);
}

void	expand_dollar_vars(char **arg, t_env_table env_table)
{
	int			i;
	t_quotes	vars;
	t_char_vec	vec;

	i = -1;
	initialize_vec_of_char(&vec);
	initialize_quotes_vars(&vars);
	while ((*arg)[++i] != '\0')
	{
		if ((*arg)[i] == SP_SINGLE_QUOTES || (*arg)[i] == SP_DOUBLE_QUOTES)
			open_and_close_quotes((*arg)[i], &vars);
		else if ((*arg)[i] == DOLLAR && vars.backslash == NONE
			&& vars.single_quotes == CLOSED)
		{
			if (vars.double_quotes == OPEND)
				expand_quoted_var(*arg, &i, &vec, env_table);
			else
				expand_unquoted_var(*arg, &i, &vec, env_table);
			continue ;
		}
		does_backslash_exist((*arg)[i], &vars);
		vec.add_new_element(&vec, (*arg)[i]);
	}
	free(*arg);
	*arg = vec.elements;
}
