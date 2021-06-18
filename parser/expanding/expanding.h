/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:39:07 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/18 11:18:28 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDING_H
# define EXPANDING_H

# include "../parser.h"

typedef struct s_expnd_vars
{
	t_char_vec	arg_vec;
	t_quotes	quotes;
}	t_expnd_vars;

void	give_quotes_special_meaning(char *str);
void	expand_dollar_vars(char **str_addr);
void	split_element_to_args(t_str_vec *vec, int *index);
void	remove_special_quotes(char **str_addr);

#endif
