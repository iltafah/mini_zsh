/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:34:46 by iltafah           #+#    #+#             */
/*   Updated: 2019/10/30 21:25:05 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*list;

	if (!(list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
