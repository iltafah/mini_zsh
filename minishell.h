#ifndef MINISHELL_H

#define MINISHELL_H
#define CYN "\e[1;96m"
#define YEL "\e[1;93m"
#define RED "\e[1;91m"
#define GRN "\e[1;92m"
#define PRP "\e[1;95m"
#define WHT "\e[1;97m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "./get_next_line/get_next_line.h"
#include "./vectors/vectors.h"

#define BOTTOM 0
#define NEXT 1

#define FALSE 0
#define TRUE 1

#define OPEND 1
#define CLOSED 0

#define NONE 0
#define EXIST 1

#define ERROR -1
#define VALID 1

#define DOUBLE_QUOTES '"'
#define SINGLE_QUOTES '\''
#define BACKSLASH '\\'
#define PIPE '|'
#define SEMICOLON ';'
#define DOLLAR '$'

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
	t_vec			args_vec;
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
									env table								
** ************************************************************************** **
*/

typedef struct s_env_table
{
	t_vec name;
	t_vec value;
} t_env_table;

// typedef struct s_env_vec
// {
// 	t_env_var *table;
// 	int size;
// 	int used_size;
// } t_env_vec;

/*
** ************************************************************************** **
*/

int check_tokens_syntax(t_tokens *tokens_list);
void line_tokenization(char *line, t_tokens **tokens_list);
void create_abstract_syntax_tree(t_ast **ast, t_tokens *tokens);
void free_tokens_list(t_tokens **tokens_list);
void free_abstract_syntax_tree(t_ast *ast);

void create_env_table(t_env_table *env_table, char **env);
#endif

// typedef enum e_special_characters
// {single_quotes = '\'', double_quotes = '"',
// backslash = '\\', semicolon = ';', pipe = '|'}
// t_special_characters;

// typedef struct          s_node
// {
//     t_tag               tag;
//     struct s_node       *bottom;
//     struct s_node       *next;

//     union               infos
//     {
//         char            *word;
//         t_redirection   *redirections;
//     }                   u_infos;

// }                       t_node;

// typedef struct			s_pipe_seq
// {
// 	char				**simple_cmd;
// 	t_redirection		*redirections;
// 	struct s_pipe_seq	*next;
// }						t_pipe_seq;

// typedef struct			s_simple_cmd
// {
// 	char				**content;
// 	int					content_size;
// 	t_redirection		*redirections;
// }						t_simple_cmd;