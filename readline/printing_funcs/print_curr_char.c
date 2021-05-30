#include "../readline.h"

int		check_if_cmd_exist(char *cmd)
{
	struct stat buffer;
	int			does_exist;

	does_exist = stat(cmd, &buffer);
	if (does_exist == 0)
		return (found);
	// else
	// {

	// }
	return (not_found);
}

char	*get_cmd_color(char *line, int *len)
{
	char	*color;
	char	*cmd;

	color = RED_MAX;
	// printf("wow\n");
	// if (line[*len] != '\0')
	while (line[*len] != '\0' && line[*len] != ' ')
		(*len)++;
	cmd = ft_substr(line, 0, *len);
	// fprintf(fd2, "len = %d str = '%s'\n", *len, cmd);
	// fflush(fd2);
	if (check_if_cmd_exist(cmd) == EXIST)
		color = GRN;
	free(cmd);
	return (color);
}

int		is_there_syntax_error(t_quotes *vars, char c)
{
	if (vars->pipe == EXIST && (c == PIPE || c == SEMICOLON))
		return (ERROR);
	else if (vars->semicolon == EXIST && (c == SEMICOLON || c == PIPE))
		return (ERROR);
	return (TRUE);
}

char	*get_highlighting_color(t_quotes *vars, char *line, int i, int *len)
{
	char	*color;

	color = WHT;
	open_and_close_quotes(line[i], vars);
	change_quotes_state(vars);
	if ((i == 0 || vars->pipe == EXIST || vars->semicolon == EXIST))
		color = get_cmd_color(line + i, len);
	if (is_there_syntax_error(vars, line[i]) == ERROR)
		return (RED_MAX);
	if (vars->curr_state != vars->old_state)
			color = PNK;
	else if (vars->double_quotes == OPEND || vars->single_quotes == OPEND)
		color = PRP;
	if (does_pipe_exist(line[i], vars) == EXIST)
		color = YEL;
	if (does_semicolon_exist(line[i], vars) == EXIST)
		color = CYN;
	if (does_backslash_exist(line[i], vars) == EXIST)
		color = ORN;
	return (color);
}

void	print_with_syntax_highlighting(t_rdline *rdl_vars)
{
	int				i;
	int				len;
	char			*color;
	t_char_vec		*hstry_line;
	t_quotes		syntax_vars;

	i = 0;
	len = 0;
	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
	save_curr_cursor_pos(rdl_vars);
	move_cursor_to_colum_and_row(rdl_vars, rdl_vars->prompt_len, 0);
	initialize_quotes_vars(&syntax_vars);
	while (i < hstry_line->used_size)
	{
		// if ((i == 0 || syntax_vars.pipe == EXIST || syntax_vars.semicolon == EXIST)
		// 	&& len == 0)
		// 	color = get_cmd_color(syntax_vars, hstry_line->elements + i, &len);
		// else if (len == 0)
		if (len == 0)
			color = get_highlighting_color(&syntax_vars, hstry_line->elements, i, &len);
		else
			len--;
		rdl_print_char(rdl_vars, hstry_line->elements[i], color);
		i++;
	}
	restore_cursor_pos(rdl_vars);
}

void	print_curr_char(t_rdline *rdl_vars, char c)
{
	t_char_vec		*history_line;
	t_vchar_vec		*history_vec;
	int				*l_i;
	int				*c_i;

	c_i = &rdl_vars->c_i;
	l_i = &rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	history_line[*l_i].add_new_element_at_index(&history_line[*l_i], c, *c_i);
	rdl_print_char(rdl_vars, history_line[*l_i].elements[*c_i], WHT);
	(*c_i)++;
	print_after_cursor(rdl_vars, history_line[*l_i].elements + *c_i, restore);
	print_with_syntax_highlighting(rdl_vars);
	print_suggestions(rdl_vars);
	update_cursor_data(rdl_vars);
}
