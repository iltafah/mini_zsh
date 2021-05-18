/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 22:23:11 by iltafah           #+#    #+#             */
/*   Updated: 2019/10/27 04:53:13 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_calc(int n)
{
	int		count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	unsigned int	num;
	int				n_digits;
	int				size;
	char			*result;

	n_digits = digits_calc(n);
	size = n < 0 ? n_digits + 1 : n_digits;
	if (!(result = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	result[0] = n < 0 ? '-' : result[0];
	result[0] = n == 0 ? '0' : result[0];
	result[size--] = '\0';
	num = n < 0 ? n * -1 : n;
	while (num != 0)
	{
		result[size--] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}
