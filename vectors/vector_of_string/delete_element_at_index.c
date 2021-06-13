/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_element_at_index.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:43:03 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:43:05 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vectors.h"

void	delete_element_at_index(t_str_vec *vec, int index)
{
	if (index < 0 || index > vec->size)
		return ;
	free(vec->elements[index]);
	while (index <= vec->used_size)
	{
		vec->elements[index] = vec->elements[index + 1];
		index++;
	}
	vec->used_size -= 1;
	if (vec->size > 0 && vec->used_size < (vec->size / 4))
	{
		vec->size /= 2;
		realloc_vector(vec);
	}
}
