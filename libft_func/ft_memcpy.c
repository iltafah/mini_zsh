/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:13:02 by iltafah           #+#    #+#             */
/*   Updated: 2019/10/26 21:07:03 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*s1;
	char		*s2;

	if (dst == 0 && src == 0)
		return (0);
	s1 = (char*)dst;
	s2 = (char*)src;
	while (n-- != 0)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	return (dst);
}
