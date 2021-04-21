#include "./expanding.h"

// void		replace_dollar(char **str_addr, t_env_table env_table)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = *str_addr;
// 	while (str[i] != '\0')
// 	{

// 	}
// }

void		expand_args_vec(t_vec *args_vec, t_env_table env_table)
{
	int		i;

	i = 0;
	while (args_vec->elements[i])
	{
		//replace_dollar(&args_vec->elements[i], env_table);
		i++;
	}
}

void		expand_curr_cmd(t_ast *curr_simple_cmd, t_env_table env_table)
{
	t_ast	*data;

	data = curr_simple_cmd->node.dir.bottom;
	expand_args_vec(&data->node.data.args_vec, env_table);
	//expand_redirection_list();
}



//[cat]  ["hello   world"] [$vscode]  [$vscode]