#include "../readline.h"

void	print_prompt(t_rdline *rdl_vars)
{
	int		i;
	char	*prompt;

	i = 0;
	prompt = rdl_vars->prompt;
	ft_putstr_fd(GRN, rdl_vars->tty_fd);
	while (prompt[i] != ' ')
		put_char(prompt[i++]);
	ft_putstr_fd(CYN, rdl_vars->tty_fd);
	while (prompt[i] != '\0')
		put_char(prompt[i++]);
	ft_putstr_fd(WHT, rdl_vars->tty_fd);
}
