#include "./readline.h"

void	enable_raw_mode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	disable_raw_mode(struct termios old_termios_state)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios_state);
}

void	read_line(char **line)
{
	static struct termios	original_termios_state;
	static int				is_initialized = false;
	t_rdline				*rdl_vars;

	rdl_vars = &g_vars.rdl_vars;
	if (is_initialized == false)
	{
		initialize_termios_struct(&original_termios_state);
		initialize_rdl_vars(rdl_vars);
		is_initialized = true;
	}
	enable_raw_mode();
	process_input(line, &g_vars.rdl_vars);
	disable_raw_mode(original_termios_state);
}
