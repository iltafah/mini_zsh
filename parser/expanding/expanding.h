/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:39:07 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:39:09 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDING_H
# define EXPANDING_H

# include "../parser.h"

void	give_quotes_special_meaning(char *str);
void    expand_dollar_vars(char **str_addr, t_env_table env_table);
void	split_element_to_args(t_str_vec *vec, int *index);
void	remove_special_quotes(char **str_addr);


#endif