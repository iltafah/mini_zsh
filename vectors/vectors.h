#include "stdlib.h"
/*
** ************************************************************************** **
								char** vector
** ************************************************************************** **
*/

typedef struct s_vec t_vec;

struct s_vec
{
	char **elements;
	int size;
	int used_size;
	void	(*add_new_element)(t_vec *, char *);
};

/*
** ************************************************************************** **
*/

void	initialize_vec_content(t_vec *vec);
void	add_new_element(t_vec *vec, char *element);
