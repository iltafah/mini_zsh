#include "readline.h"

void	restore_cursor_pos(t_rdline *rdl_vars)
{
	t_int_vec	*old_colm_stack;
	t_int_vec	*old_row_stack;
	int			old_curs_colm_pos;
	int			old_curs_row_pos;

	old_colm_stack = &rdl_vars->old_curs_colm_pos_stack;
	old_row_stack = &rdl_vars->old_curs_row_pos_stack;
	old_colm_stack->pop_element(old_colm_stack, &old_curs_colm_pos);
	old_row_stack->pop_element(old_row_stack, &old_curs_row_pos);
	while (rdl_vars->curs_row_pos > old_curs_row_pos)
		move_cursor_up_vertically(rdl_vars);
	move_cursor_to_colum(rdl_vars, old_curs_colm_pos);
}

void	save_curr_cursor_pos(t_rdline *rdl_vars)
{
	t_int_vec	*old_colm_stack;
	t_int_vec	*old_row_stack;

	old_colm_stack = &rdl_vars->old_curs_colm_pos_stack;
	old_row_stack = &rdl_vars->old_curs_row_pos_stack;
	old_colm_stack->push_element(old_colm_stack, rdl_vars->curs_colm_pos);
	old_row_stack->push_element(old_row_stack, rdl_vars->curs_row_pos);
}
