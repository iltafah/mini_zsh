/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_time.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:45:57 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:45:58 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREEING_TIME_H
# define FREEING_TIME_H

// # include "../minishell.h"
# include "../parser/parser.h"

void	free_array(char ***array_addr);
void	free_tokens_list(t_tokens **tokens_list);
void	free_abstract_syntax_tree(t_ast *ast);

#endif