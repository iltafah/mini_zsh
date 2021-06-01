#include "./readline.h"

int		open_history_file(t_rdline *rdl_vars, int o_flag)
{
	char	*hstry_file_path;
	char	*home_directory;
	int		history_fd;

	history_fd = -1;
	home_directory = getenv("HOME");
	if (home_directory != NULL)
	{
		hstry_file_path = ft_strjoin(home_directory, "/.minishell_history");
		history_fd = open(hstry_file_path, o_flag, 0600);
		free(hstry_file_path);
	}
	return (history_fd);
}
