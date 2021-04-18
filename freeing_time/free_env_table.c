#include "./freeing_time.h"

void	free_env_table(t_env_vec *env_vec)
{
	int		i;

	i = 0;
	while (i < env_vec->used_size)
	{
		free(env_vec->table[i].name);
		free(env_vec->table[i].value);
		i++;
	}
	free(env_vec->table);
	env_vec->table = NULL;
}