#include "./freeing_time.h"

void	free_tokens_list(t_tokens **tokens_list)
{
	t_tokens	*curr_token;
	t_tokens	*next_token;

	curr_token = *tokens_list;
	while (curr_token)
	{
		next_token = curr_token->next;
		if (curr_token->data != NULL)
		{
			free(curr_token->data);
			curr_token->data = NULL;
		}
		free(curr_token);
		curr_token = NULL;
		curr_token = next_token;
	}
	*tokens_list = NULL;
}