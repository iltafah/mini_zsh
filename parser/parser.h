#ifndef PARSER_H
# define PARSER_H

# define BOTTOM 0
# define NEXT 1

# define FALSE 0
# define TRUE 1

# define OPEND 1
# define CLOSED 0

# define NONE 0
# define EXIST 1

# define ERROR -1
# define VALID 1

# define DOUBLE_QUOTES '"'
# define SINGLE_QUOTES '\''
# define BACKSLASH '\\'
# define PIPE '|'
# define SEMICOLON ';'
# define DOLLAR '$'

# define CYN "\e[1;96m"
# define YEL "\e[1;93m"
# define RED "\e[1;91m"
# define GRN "\e[1;92m"
# define PRP "\e[1;95m"
# define WHT "\e[1;97m"

# include "stdio.h"
# include "../vectors/vectors.h"
# include "../environment/environment.h"
# include "./usefull_functions/usefull_functions.h"
# include "../libft/libft.h"

typedef enum e_tag
{
	e_cmdline_node,
	e_pipeline_node,
	e_simple_cmd_node,
	e_data_node
} t_tag;

typedef enum e_type
{
	e_start,
	e_pipe,
	e_semicolon,
	e_simple_word,
	e_redir,
	newline
} t_type;


/*
** ************************************************************************** **
							redirection linked list
** ************************************************************************** **
*/

typedef struct s_redirection
{
	char *type;
	char *file;
	struct s_redirection *next;
} t_redirection;

/*
** ************************************************************************** **
						abstruct syntax tree struct
** ************************************************************************** **
*/

typedef struct s_data
{
	//char **args;
	t_str_vec		args_vec;
	t_redirection	*redirections;
} t_data;

typedef struct s_dir
{
	struct s_ast *next;
	struct s_ast *bottom;
} t_dir;

typedef struct s_ast
{
	t_tag tag;
	union u_node
	{
		t_dir dir;
		t_data data;
	} node;
} t_ast;

/*
** ************************************************************************** **
						tokens linked list struct
** ************************************************************************** **
*/

typedef struct s_tokens
{
	char *data;
	t_type type;
	struct s_tokens *next;
} t_tokens;

/*
** ************************************************************************** **
*/

#endif