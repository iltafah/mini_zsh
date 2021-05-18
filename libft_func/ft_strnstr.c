/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:10:36 by iltafah           #+#    #+#             */
/*   Updated: 2019/11/19 09:01:55 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	i;
	size_t	n;

	s1 = (char*)haystack;
	s2 = (char*)needle;
	if (!*needle)
		return (s1);
	if (len)
		while (*s1 && len--)
		{
			i = 0;
			n = len;
			if (s1[i] == s2[i])
			{
				i++;
				while (s1[i] == s2[i] && s2[i] && s1[i] && n--)
					i++;
				if (!s2[i])
					return (s1);
			}
			s1++;
		}
	return (NULL);
}
