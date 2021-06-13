/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char_at_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:44:16 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:44:17 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vectors.h"

void	delete_char_at_index(t_char_vec *vec, int index)
{
	if (index < 0 || index > vec->used_size)
		return ;
	vec->elements[index] = '\0';
	while (index <= vec->used_size)
	{
		vec->elements[index] = vec->elements[index + 1];
		index++;
	}
	vec->used_size -= 1;
	if (vec->used_size > 0)
		vec->last_index = vec->used_size - 1;
	if (vec->size > 0 && vec->used_size < (vec->size / 4))
	{
		vec->size /= 2;
		realloc_char_vector(vec, vec->size);
	}
}
