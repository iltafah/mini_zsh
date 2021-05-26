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
		signal(SIGINT, signals_handler);
		signal(SIGWINCH, signals_handler);
		is_initialized = true;
	}
	enable_raw_mode();
	process_input(line, rdl_vars);
	disable_raw_mode(original_termios_state);
}
