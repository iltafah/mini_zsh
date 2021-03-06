/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shift_left_arrow_action.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:50:54 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:50:55 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_shift_left_arrow_action(t_rdline *rdl_vars)
{
	start_highlighting_mode(rdl_vars);
	left_highlight(rdl_vars);
}
