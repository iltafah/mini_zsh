#include "./readline.h"

void	overwrite_history_file(t_rdline *rdl_vars)
{
	char			*line;
	int				line_index;
	int				history_fd;
	t_vchar_vec		*history_vec;

	history_fd = open_history_file((O_CREAT | O_WRONLY | O_TRUNC));
	if (history_fd == -1)
		return ;
	history_vec = &rdl_vars->history_vec;
	line_index = 0;
	while (line_index <= history_vec->last_index)
	{
		line = history_vec->elements[line_index].elements;
		write(history_fd, line, history_vec->elements[line_index].used_size);
		write(history_fd, "\n", 1);
		line_index++;
	}
	if (history_vec->last_index != 0 && line_index == history_vec->last_index)
		write(history_fd, line, history_vec->elements[line_index].used_size);
	close(history_fd);
}
