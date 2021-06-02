#include "./minishell.h"

char	*get_prompt_name(void)
{
	static char	arrow[] = "༺  ";
	static char	spaces[] = " ";
	char		*curr_dir;
	char		*tmp_ptr;
	char		*prompt;

	prompt = NULL;
	curr_dir = get_curr_dir_name();
	if (curr_dir != NULL)
	{
		prompt = ft_strjoin(arrow, curr_dir);
		free(curr_dir);
		tmp_ptr = ft_strjoin(prompt, spaces);
		free(prompt);
		prompt = tmp_ptr;
	}
	return (prompt);
}
