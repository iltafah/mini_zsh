#include "./expanding.h"

void		expand_args(char ***args_table)
{
	
}

void		expand_curr_cmd(t_ast *curr_simple_cmd)
{
	t_ast	*data;

	data = curr_simple_cmd->node.dir.bottom;
	expand_args(&data->node.data.args);
}