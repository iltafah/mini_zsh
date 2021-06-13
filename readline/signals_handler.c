/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:46:57 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:46:59 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	show_new_prompt(void)
{
	t_vchar_vec		*history_vec;

	history_vec = &g_vars.rdl_vars.history_vec;
	quit_highlighting_mode(&g_vars.rdl_vars, enter);
	g_vars.rdl_vars.history_vec.delete_last_element(history_vec);
	add_empty_char_vec_to_history_vec(history_vec);
	g_vars.rdl_vars.c_i = 0;
	g_vars.rdl_vars.l_i = g_vars.rdl_vars.history_vec.last_index;
	g_vars.rdl_vars.curs_row_pos = 0;
	g_vars.rdl_vars.curs_colm_pos = g_vars.rdl_vars.prompt_len;
	printf("\n");
	print_prompt(&g_vars.rdl_vars);
}

void	signals_handler(int sig_num)
{
	if (sig_num == SIGWINCH)
		detect_screen_resizing(&g_vars.rdl_vars);
	else if (sig_num == SIGINT)
		show_new_prompt();
}
