/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:15:14 by iltafah           #+#    #+#             */
/*   Updated: 2019/10/20 17:50:46 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*r;
	int		len;

	r = (char*)s;
	len = ft_strlen(s) + 1;
	while (len--)
	{
		if (*r == (char)c)
			return (r);
		r++;
	}
	return (NULL);
}
