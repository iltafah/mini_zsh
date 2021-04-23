#ifndef VECTOR_H
#define VECTOR_H
# include "stdlib.h"
/*
** ************************************************************************** **
								string vector
** ************************************************************************** **
*/

typedef struct s_str_vec t_str_vec;

struct s_str_vec
{
	char	**elements;
	int		size;
	int		used_size;
	void	(*add_new_element)(t_str_vec *, char *);
	void	(*add_new_element_at_index)(t_str_vec *, char *, int);
	void	(*replace_element_at_index)(t_str_vec *, char *, int);
	void	(*delete_element_at_index)(t_str_vec *, int);
	void	(*free)(t_str_vec *);	
};

/*
** ************************************************************************** **
								char vector
** ************************************************************************** **
*/

typedef struct s_char_vec t_char_vec;

struct s_char_vec
{
	char	*elements;
	int		size;
	int		used_size;
	void	(*add_new_element)(t_char_vec *, char);
	void	(*add_new_element_at_index)(t_char_vec *, char , int);
	void	(*add_set_of_elements_at_index)(t_char_vec *, char *, int);
	void	(*replace_element_at_index)(t_char_vec *, char , int);
	void	(*delete_element_at_index)(t_char_vec *, int);
	void	(*free)(t_char_vec *);	
};

/*
** ************************************************************************** **
*/

char	*ft_strdup(const char *s1);
void	initialize_vec_content(t_str_vec *vec);
void	add_new_element(t_str_vec *vec, char *element);
void	add_new_element_at_index(t_str_vec *vec, char *element, int index);
void	replace_element_at_index(t_str_vec *vec, char *element, int index);
void	delete_element_at_index(t_str_vec *vec, int index);
void	vector_free(t_str_vec *vec);

void	initialize_vec_of_char(t_char_vec *vec);
void	add_new_char(t_char_vec *vec, char c);
void	delete_char_at_index(t_char_vec *vec, int index);
void	add_new_char_at_index(t_char_vec *vec, char c, int index);
void    add_set_of_chars_at_index(t_char_vec *vec, char *str, int index);
void	replace_char_at_index(t_char_vec *vec, char c, int index);
void	char_vector_free(t_char_vec *vec);

#endif