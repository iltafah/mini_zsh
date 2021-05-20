#include "../readline.h"

void	print_prompt(t_rdline *rdl_vars)
{
	int		i;
	char	*prompt;

	i = 0;
	prompt = rdl_vars->prompt;
	write(1, GRN, ft_strlen(GRN));
	while (prompt[i] != ' ')
		put_char(prompt[i++]);
	write(1, CYN, ft_strlen(CYN));
	while (prompt[i] != '\0')
		put_char(prompt[i++]);
	write(1, WHT, ft_strlen(WHT));
}
