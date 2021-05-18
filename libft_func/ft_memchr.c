/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:29:42 by iltafah           #+#    #+#             */
/*   Updated: 2019/10/25 07:29:59 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *a;

	a = (unsigned char*)s;
	while (n--)
	{
		if (*a == (unsigned char)c)
			return (a);
		a++;
	}
	return (0);
}
