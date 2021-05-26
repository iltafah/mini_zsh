#include "./readline.h"

void	load_history(t_rdline *rdl_vars)
{
	char			*line;
	t_char_vec		new_vec;
	int				history_fd;
	t_vchar_vec		*history_vec;
	int				is_not_last_line;

	history_fd = open_history_file(rdl_vars, (O_CREAT | O_RDONLY));
	history_vec = &rdl_vars->history_vec;
	is_not_last_line = true;
	while (is_not_last_line == true)
	{
		is_not_last_line = get_next_line(history_fd, &line);
		if (is_not_last_line == true)
		{
			new_vec = convert_string_to_char_vec(line);
			history_vec->add_new_element(history_vec, new_vec);
			free(line);
		}
	}
	close(history_fd);
}
