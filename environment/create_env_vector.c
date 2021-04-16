#include "./environment.h"

void	initialize_env_vector(t_env_vec *env_vec)
{
	env_vec->table = malloc(sizeof(t_env_var) * 2);
	env_vec->size = 2;
	env_vec->used_size = 0;
}

void	realloc_dynamic_table(t_env_vec *env_vec)
{
	int			i;
	t_env_var	*new_table;

	i = 0;
	env_vec->size *= 2;
	new_table = malloc(sizeof(t_env_var) * (env_vec->size + 1));
	while (i < env_vec->used_size)
	{
		new_table[i].name = env_vec->table[i].name;
		new_table[i].value = env_vec->table[i].value;
		i++;
	}
	free(env_vec->table);
	env_vec->table = new_table;
}

void	extract_name_and_value_from_env(t_env_vec *env_vec, char *env_str)
{
	int		len;

	len = 0;
	while (env_str[len] != '=')
		len++;
	env_vec->table[env_vec->used_size].name = ft_substr(env_str, 0, len);
	env_vec->table[env_vec->used_size].value = ft_strdup(env_str + len + 1);
}

void	add_element_to_dynamic_table(t_env_vec *env_vec, char *env_str)
{
	if (env_vec->used_size == env_vec->size)
		realloc_dynamic_table(env_vec);
	extract_name_and_value_from_env(env_vec, env_str);
	env_vec->used_size += 1;
}

void	create_env_vector(t_env_vec *env_vec, char **env)
{
	int		i;

	initialize_env_vector(env_vec);	
	i = -1;
	while (env[++i])
		add_element_to_dynamic_table(env_vec, env[i]);
}