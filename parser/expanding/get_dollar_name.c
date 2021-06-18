/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollar_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 21:47:00 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/18 21:47:22 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expanding.h"

char	*get_dollar_name(char *str, int *index_addr)
{
	int		i;
	int		len;
	int		start;
	char	*name;

	start = *index_addr + 1;
	i = start;
	len = 0;
	name = NULL;
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
	if (len > 0)
	{
		name = ft_substr(str, start, len);
		*index_addr = i;
	}
	return (name);
}
