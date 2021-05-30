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

	// fprintf(fd2, CYN);
	// fprintf(fd2, "\n===============after poping===============\n");
	// fprintf(fd2, WHT);
	// fprintf(fd2, "old_colm_stak:\n");
	// for(int i = 0; i < old_colm_stack->used_size; i++)
	// {
	// 	fprintf(fd2, "%d ", old_colm_stack->elements[i]);
	// }
	// fprintf(fd2, "\nold_row_stak:\n");
	// for(int i = 0; i < old_row_stack->used_size; i++)
	// {
	// 	fprintf(fd2, "%d ", old_row_stack->elements[i]);
	// }
	// fflush(fd2);
}

void	save_curr_cursor_pos(t_rdline *rdl_vars)
{
	t_int_vec 	*old_colm_stack;
	t_int_vec	*old_row_stack;

	old_colm_stack = &rdl_vars->old_curs_colm_pos_stack;
	old_row_stack = &rdl_vars->old_curs_row_pos_stack;
	old_colm_stack->push_element(old_colm_stack, rdl_vars->curs_colm_pos);
	old_row_stack->push_element(old_row_stack, rdl_vars->curs_row_pos);
	
	// fprintf(fd2, GRN);
	// fprintf(fd2, "\n===============after pushing===============\n");
	// fprintf(fd2, WHT);
	// fprintf(fd2, "old_colm_stak:\n");
	// for(int i = 0; i < old_colm_stack->used_size; i++)
	// {
	// 	fprintf(fd2, "%d ", old_colm_stack->elements[i]);
	// }
	// fprintf(fd2, "\nold_row_stak:\n");
	// for(int i = 0; i < old_row_stack->used_size; i++)
	// {
	// 	fprintf(fd2, "%d ", old_row_stack->elements[i]);
	// }
	// fflush(fd2);
}
