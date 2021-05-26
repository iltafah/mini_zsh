#include "./readline.h"

void	enable_raw_mode(void)
{
	struct termios	raw;

	tcgetattr(g_vars.rdl_vars.tty_fd, &raw);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw.c_iflag &= ~(IXON);
	tcsetattr(g_vars.rdl_vars.tty_fd, TCSAFLUSH, &raw);
}

void	disable_raw_mode(struct termios old_termios_state)
{
	tcsetattr(g_vars.rdl_vars.tty_fd, TCSAFLUSH, &old_termios_state);
}

void	open_history_file(t_rdline *rdl_vars)
{
	char	*hstry_file_path;
	char	*home_directory;

	home_directory = getenv("HOME");
	hstry_file_path = ft_strjoin(home_directory, "/.minishell_history");
	rdl_vars->history_fd = open(hstry_file_path, O_RDWR | O_CREAT, 0600);
	free(hstry_file_path);
}

void	load_history(t_rdline *rdl_vars)
{
	char			*line;
	int				is_not_last_line;
	t_vchar_vec		*history_vec;
	t_char_vec		new_vec;

	open_history_file(rdl_vars);
	history_vec = &rdl_vars->history_vec;
	is_not_last_line = true;
	while (is_not_last_line == true)
	{
		is_not_last_line = get_next_line(rdl_vars->history_fd, &line);
		if (is_not_last_line == true)
		{
			new_vec = convert_string_to_char_vec(line);
			history_vec->add_new_element(history_vec, new_vec);
			free(line);
		}
	}
}

void	read_line(char **line)
{
	static struct termios	original_termios_state;
	static int				is_initialized = false;
	t_rdline				*rdl_vars;

	rdl_vars = &g_vars.rdl_vars;
	if (is_initialized == false)
	{
		initialize_rdl_vars(rdl_vars);
		initialize_termios_struct(&original_termios_state);
		initialize_capabilities(&rdl_vars->capability);
		load_history(rdl_vars);
		is_initialized = true;
	}
	enable_raw_mode();
	process_input(line, rdl_vars);
	disable_raw_mode(original_termios_state);
}
