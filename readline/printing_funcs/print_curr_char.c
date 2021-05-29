#include "../readline.h"

char	*get_cmd_color(t_quotes vars, char *line, int *len)
{
	char	*color;
	char	*cmd;

	len = 0;
	color = GRN;
	printf("wow\n");
	if (line[*len] != '\0')
	while (line[*len + 1] != '\0' && line[*len + 1] != ' ')
		(*len)++;
	cmd = ft_substr(line, 0, *len);
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

char	*determine_syntax_highlighting_color(t_quotes *vars, char c)
{
	char	*color;

	color = WHT;
	open_and_close_quotes(c, vars);
	change_quotes_state(vars);
	if (is_there_syntax_error(vars, c) == ERROR)
		return (RED_MAX);
	if (vars->curr_state != vars->old_state)
	{
		if (c == SINGLE_QUOTES || c == DOUBLE_QUOTES)
			color = PNK;
	}
	else if (vars->double_quotes == OPEND || vars->single_quotes == OPEND)
		color = PRP;
	if (does_pipe_exist(c, vars) == EXIST)
		color = YEL;
	else if (does_semicolon_exist(c, vars) == EXIST)
		color = CYN;
	else if (does_backslash_exist(c, vars) == EXIST)
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
		// else
			color = determine_syntax_highlighting_color(&syntax_vars,
				hstry_line->elements[i]);
		rdl_print_char(rdl_vars, hstry_line->elements[i], color);
		// if (len > 0)
		// 	len--;
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
